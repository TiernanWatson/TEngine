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

		void Render(float32 deltaTime);

		void ClearBuffer(float r, float g, float b);
		void DrawIndexed(int count);
		void Draw(int count);
		void Present();

	private:
		// DirectX 11 device info and swap chain
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer;

		friend class Bindable;  // For access to context and device
	};
}
