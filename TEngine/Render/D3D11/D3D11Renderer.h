#pragma once
#include "../../Platform/Windows/WinHeader.h"
#include <wrl.h>
#include <d3d11.h>
#include <unordered_map>
#include "../../Core/PortableTypes.h"
#include "DXGraphicsExceptions.h"

namespace TEngine
{
	class WorldSystem;
	class World;
	class Mesh;
	class Matrix4;

	class D3D11Renderer
	{
	public:
		D3D11Renderer();
		D3D11Renderer(const D3D11Renderer&) = delete;
		D3D11Renderer& operator=(const D3D11Renderer&) = delete;

		void StartUp();
		void ShutDown();

		void Render(F32 delta_time);

		void ClearBuffer(float r, float g, float b);
		void DrawIndexed(int count);
		void Draw(int count);
		void Present();

	private:
		// DirectX 11 device_ info and swap chain
		Microsoft::WRL::ComPtr<ID3D11Device> device_;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_;

		friend class Bindable;  // For access to context_ and device_
	};
}
