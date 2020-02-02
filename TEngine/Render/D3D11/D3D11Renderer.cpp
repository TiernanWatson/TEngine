#pragma comment(lib,"d3d11.lib")  // For D3D11 in general
#pragma comment(lib, "D3DCompiler.lib")  // For compiling shaders

#include "D3D11Renderer.h"
#include "../../Platform/Windows/WindowsOS.h"
#include "../../Core/Math/TMath.h"
#include "../../Core/Math/Matrix4.h"
#include "../../Core/Math/Vector3.h"
#include "../Vertex.h"
#include "../../Resources/Types/Mesh.h"
#include "Bindables/DXConstantBuffer.h"
#include "Bindables/DXInputLayout.h"
#include "Bindables/DXPixelShader.h"
#include "Bindables/DXVertexBuffer.h"
#include "Bindables/DXVertexShader.h"
#include "Bindables/DXSampler.h"
#include "DXMeshInstance.h"
#include <d3dcompiler.h>

#include "../../World/World.h"
#include "../../World/WorldSystem.h"
#include "../../ECS/Components/MeshComponent.h"
#include "../../ECS/Components/Transform.h"
#include "../../ECS/Components/Camera.h"

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	D3D11Renderer::D3D11Renderer()
	{
	}

	void D3D11Renderer::StartUp()
	{
		/*
		* First get device, context and swapchain
		*/

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = WindowsOS::GetInstance().GetWidth();
		sd.BufferDesc.Height = WindowsOS::GetInstance().GetHeight();
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = WindowsOS::GetInstance().GetHWND();
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		UINT flags = 0;
#if _DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
		HRESULT hr;
		THROW_IF_FAIL(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&swapChain,
			&device,
			nullptr,
			&context
		));

		/*
		* Get the render target
		*/

		wrl::ComPtr<ID3D11Resource> backBuffer;
		THROW_IF_FAIL(swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer));
		THROW_IF_FAIL(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget));

		D3D11_DEPTH_STENCIL_DESC dDesc = {};
		dDesc.DepthEnable = TRUE;
		dDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dDesc.DepthFunc = D3D11_COMPARISON_LESS;

		wrl::ComPtr<ID3D11DepthStencilState> dsState;
		THROW_IF_FAIL(device->CreateDepthStencilState(&dDesc, &dsState));
		context->OMSetDepthStencilState(dsState.Get(), 1);

		/*
		* Setup Z-Buffering
		*/

		wrl::ComPtr<ID3D11Texture2D> depthStencilTex;
		D3D11_TEXTURE2D_DESC dTexDesc = {};
		dTexDesc.Width = WindowsOS::GetInstance().GetWidth();
		dTexDesc.Height = WindowsOS::GetInstance().GetHeight();
		dTexDesc.MipLevels = 1;
		dTexDesc.ArraySize = 1;
		dTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dTexDesc.SampleDesc.Count = 1;
		dTexDesc.SampleDesc.Quality = 0;
		dTexDesc.Usage = D3D11_USAGE_DEFAULT;
		dTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		THROW_IF_FAIL(device->CreateTexture2D(&dTexDesc, nullptr, &depthStencilTex));

		D3D11_DEPTH_STENCIL_VIEW_DESC dDSV = {};
		dDSV.Format = DXGI_FORMAT_D32_FLOAT;
		dDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dDSV.Texture2D.MipSlice = 0;
		THROW_IF_FAIL(device->CreateDepthStencilView(depthStencilTex.Get(), &dDSV, &depthStencilView));
		
		context->OMSetRenderTargets(1, renderTarget.GetAddressOf(), depthStencilView.Get());

		/*
		*  Setup shaders, input layout and viewport
		*/

		DXVertexShader vertexShader(*this, L"VertexShader.cso");
		vertexShader.Bind();

		DXPixelShader pixelShader(*this, L"PixelShader.cso");
		pixelShader.Bind();

		// Create Input layout

		const D3D11_INPUT_ELEMENT_DESC ed[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DXInputLayout inputLayout(*this, ed, (UINT)3, vertexShader.GetBlob());
		inputLayout.Bind();

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)WindowsOS::GetInstance().GetWidth();
		vp.Height = (FLOAT)WindowsOS::GetInstance().GetHeight();
		vp.MaxDepth = 1;
		vp.MinDepth = 0;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		context->RSSetViewports(1, &vp);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Set up rasterizer state
		D3D11_RASTERIZER_DESC rd = {};
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		rd.FrontCounterClockwise = TRUE;
		rd.DepthBias = 0;
		rd.DepthBiasClamp = 0;
		rd.SlopeScaledDepthBias = 0;
		rd.DepthClipEnable = TRUE;
		rd.ScissorEnable = FALSE;
		rd.MultisampleEnable = FALSE;
		rd.AntialiasedLineEnable = FALSE;

		THROW_IF_FAIL(device->CreateRasterizerState(&rd, &rasterizer));

		context->RSSetState(rasterizer.Get());

		DXSampler sampler(*this);
		sampler.Bind();
	}

	void D3D11Renderer::Render(float32 deltaTime)
	{
		WorldSystem& worldSys = Engine::Get().GetWorldSys();
		World* world = worldSys.GetCurrentWorld();

		Camera& cam = world->GetEntities().GetComponent<Camera>(world->GetMainCameraEnt());
		Transform& camTransform = world->GetEntities().GetComponent<Transform>(world->GetMainCameraEnt());

		struct CBuf
		{
			Matrix4 model;
			Matrix4 view;
			Matrix4 proj;
		};

		CBuf cb = {};
		cb.view = Matrix4::ModelToWorld(camTransform.position, camTransform.scale, camTransform.rotation).Inverse().Transpose();
		cb.proj = Matrix4::Projection(cam.FOV, cam.aspect, cam.farDist, cam.nearDist).Transpose();

		DXVSConstantBuffer<CBuf> constBuffer(*this, cb);
		constBuffer.Bind();

		world->GetEntities().ForEach<Transform, MeshComponent>(
			[this, &constBuffer, &cb](Transform* t, MeshComponent* m)
			{
				cb.model = Matrix4::ModelToWorld(t->position, t->scale, t->rotation).Transpose();

				constBuffer.Update(cb);

				DXMeshInstance i(*this, m->mesh);
				i.Draw();
			}
		);
	}

	void D3D11Renderer::ClearBuffer(float r, float g, float b)
	{
		const float color[] = { r, g, b, 1.f };
		context->ClearRenderTargetView(renderTarget.Get(), color);
		context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
	}

	void D3D11Renderer::DrawIndexed(int count)
	{
		context->DrawIndexed(count, 0, 0);
	}

	void D3D11Renderer::Draw(int count)
	{
		context->Draw(count, 0);
	}

	void D3D11Renderer::Present()
	{
		HRESULT hr;
		if (FAILED(hr = swapChain->Present(1u, 0u)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				throw DEVICE_REMOVED_EXCEPT(device->GetDeviceRemovedReason(), hr);
			}
			else 
			{
				throw HR_D3D11_EXCEPT(hr);
			}
		}
	}

	void D3D11Renderer::ShutDown()
	{
	}

	D3D11Exception::D3D11Exception(const char* msg, const char* file, int line) noexcept
		: Exception(msg, file, line)
	{
	}

	HrD3D11Exception::HrD3D11Exception(HRESULT hr, const char* file, int line) noexcept
		: hr(hr), D3D11Exception("HRESULT FAILED", file, line)
	{
	}

	DeviceRemovedException::DeviceRemovedException(HRESULT reason, HRESULT hr, const char* file, int line) noexcept
		: reason(reason), HrD3D11Exception(hr, file, line)
	{
	}
}
