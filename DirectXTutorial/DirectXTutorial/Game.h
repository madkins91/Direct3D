#pragma once

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;
using namespace Platform;

struct VERTEX
{
	float X, Y, Z;    // vertex position
	float R, G, B;	  // color
};

struct OFFSET
{
	float X, Y, Z;
};

class CGame
{
public:
	ComPtr<ID3D11Device1> dev;              // the device interface
	ComPtr<ID3D11DeviceContext1> devcon;    // the device context interface
	ComPtr<IDXGISwapChain1> swapchain;      // the swap chain interface
	ComPtr<ID3D11RenderTargetView> rendertarget;
	ComPtr<ID3D11Buffer> vertexbuffer;
	ComPtr<ID3D11Buffer> constantbuffer;
	ComPtr<ID3D11VertexShader> vertexshader;
	ComPtr<ID3D11PixelShader> pixelshader;
	ComPtr<ID3D11InputLayout> inputlayout;

	void InitGraphics();
	void InitPipeline();
	void Initialize();
	void Update();
	void Render();
};