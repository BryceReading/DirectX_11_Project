#pragma once
#include "AdaptorReader.h"
#include "Shaders.h"
#include "Vertex.h"

class Graphics
{
public:
	bool Initialize(HWND hWnd, int width, int height);
	void frameRender();
private:
	bool InitializeDX(HWND hwnd, int width, int height);
	bool shaderInitizer();
	bool sceneInitizer();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	VertexShader vertexShader;
	
	PixelShader pixel;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

};