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

#include <sstream>

#include "../UI/Font.h"
#include "../UI/Character.h"

namespace wrl = Microsoft::WRL;

namespace TEngine
{
	D3D11Renderer::D3D11Renderer()
	{
	}

	void D3D11Renderer::StartUp()
	{
		/*
		* First get device_, context_ and swapchain
		*/

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = WindowsOS::Get().GetWidth();
		sd.BufferDesc.Height = WindowsOS::Get().GetHeight();
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = WindowsOS::Get().GetHWND();
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		UINT flags = 0;
#if _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
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
			&swap_chain_,
			&device_,
			nullptr,
			&context_
		));

		/*
		* Get the render target
		*/

		wrl::ComPtr<ID3D11Resource> back_buffer;
		THROW_IF_FAIL(swap_chain_->GetBuffer(0, __uuidof(ID3D11Resource), &back_buffer));
		THROW_IF_FAIL(device_->CreateRenderTargetView(back_buffer.Get(), nullptr, &render_target_));

		/*
		* Setup Z-Buffering
		*/

		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
		depth_stencil_desc.DepthEnable = TRUE;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

		wrl::ComPtr<ID3D11DepthStencilState> depth_stencil_state;
		THROW_IF_FAIL(device_->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state));
		context_->OMSetDepthStencilState(depth_stencil_state.Get(), 1);
		
		wrl::ComPtr<ID3D11Texture2D> depth_stencil_tex;
		D3D11_TEXTURE2D_DESC tex_desc = {};
		tex_desc.Width = WindowsOS::Get().GetWidth();
		tex_desc.Height = WindowsOS::Get().GetHeight();
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		THROW_IF_FAIL(device_->CreateTexture2D(&tex_desc, nullptr, &depth_stencil_tex));

		D3D11_DEPTH_STENCIL_VIEW_DESC ds_view_desc = {};
		ds_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
		ds_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		ds_view_desc.Texture2D.MipSlice = 0;
		THROW_IF_FAIL(device_->CreateDepthStencilView(depth_stencil_tex.Get(), &ds_view_desc, &depth_stencil_view_));
		
		context_->OMSetRenderTargets(1, render_target_.GetAddressOf(), depth_stencil_view_.Get());
		//context_->OMSetRenderTargets(1, render_target_.GetAddressOf(), nullptr);

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)WindowsOS::Get().GetWidth();
		vp.Height = (FLOAT)WindowsOS::Get().GetHeight();
		vp.MaxDepth = 1;
		vp.MinDepth = 0;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		context_->RSSetViewports(1, &vp);

		context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Set kUp rasterizer_ state
		D3D11_RASTERIZER_DESC rd = {};
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		rd.FrontCounterClockwise = FALSE;
		rd.DepthBias = 0;
		rd.DepthBiasClamp = 0;
		rd.SlopeScaledDepthBias = 0;
		rd.DepthClipEnable = TRUE;
		rd.ScissorEnable = FALSE;
		rd.MultisampleEnable = FALSE;
		rd.AntialiasedLineEnable = FALSE;

		THROW_IF_FAIL(device_->CreateRasterizerState(&rd, &rasterizer_));

		context_->RSSetState(rasterizer_.Get());

		DXSampler sampler(*this);
		sampler.Bind();

		ID3D11BlendState* blendState = NULL;

		D3D11_BLEND_DESC blendDesc = { };
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		device_->CreateBlendState(&blendDesc, &blendState);

		context_->OMSetBlendState(blendState, NULL, 0xFFFFFFFF);

		//--------------
		WorldSystem& world_sys = Engine::Get().GetWorldSys();
		World* world = world_sys.GetCurrentWorld();

		world->GetEntities().ForEach<Transform, MeshComponent>(
			[this](Transform* t, MeshComponent* m)
			{
				m->mesh_instance = new DXMeshInstance(*this, m->mesh);
			}
		);
	}

	void D3D11Renderer::Render(F32 deltaTime)
	{
		WorldSystem& world_sys = Engine::Get().GetWorldSys();
		World* world = world_sys.GetCurrentWorld();

		Camera& cam = world->GetEntities().GetComponent<Camera>(world->GetMainCameraEnt());
		Transform& cam_transform = world->GetEntities().GetComponent<Transform>(world->GetMainCameraEnt());

		/*
		*  Setup shaders, input_ layout and viewport
		*/

		DXVertexShader vertex_shader(*this, L"VertexShader.cso");
		vertex_shader.Bind();

		DXPixelShader pixel_shader(*this, L"PixelShader.cso");
		pixel_shader.Bind();

		// Create Input layout

		const D3D11_INPUT_ELEMENT_DESC ed[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DXInputLayout input_layout(*this, ed, (UINT)3, vertex_shader.GetBlob());
		input_layout.Bind();

		struct CBuf
		{
			Matrix4 model;
			Matrix4 view;
			Matrix4 proj;
		};

		CBuf cb = {};
		cb.view = Matrix4::ModelToWorld(cam_transform.position, cam_transform.scale, cam_transform.rotation).Inverse().Transpose();
		cb.proj = Matrix4::Projection(cam.fov, cam.aspect, cam.far_dist, cam.near_dist).Transpose();

		std::stringstream ss;
		ss << "Cam Position: " << cam_transform.position.ToString() << "\n";
		OutputDebugString(ss.str().c_str());

		DXVSConstantBuffer<CBuf> const_buffer(*this, cb);
		const_buffer.Bind();

		world->GetEntities().ForEach<Transform, MeshComponent>(
			[this, &const_buffer, &cb](Transform* t, MeshComponent* m)
			{
				cb.model = Matrix4::ModelToWorld(t->position, t->scale, t->rotation).Transpose();
				const_buffer.Update(cb);

				m->mesh_instance->Draw();
			}
		);
	}

	void D3D11Renderer::ClearBuffer(float r, float g, float b)
	{
		const float color[] = { r, g, b, 1.f };
		context_->ClearRenderTargetView(render_target_.Get(), color);
		context_->ClearDepthStencilView(depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
	}

	void D3D11Renderer::DrawIndexed(int count)
	{
		context_->DrawIndexed(count, 0, 0);
	}

	void D3D11Renderer::Draw(int count)
	{
		context_->Draw(count, 0);
	}

	void D3D11Renderer::Present()
	{
		HRESULT hr;
		if (FAILED(hr = swap_chain_->Present(0, 0)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				throw DEVICE_REMOVED_EXCEPT(device_->GetDeviceRemovedReason(), hr);
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
		: hr_(hr), D3D11Exception("HRESULT FAILED", file, line)
	{
	}

	DeviceRemovedException::DeviceRemovedException(HRESULT reason, HRESULT hr, const char* file, int line) noexcept
		: reason_(reason), HrD3D11Exception(hr, file, line)
	{
	}
}
