#pragma once
#include "AdaptorReader.h"
#include "Shaders.h"

class Graphics
{
public:
	bool Initialize(HWND hWnd, int width, int height);
	void frameRender();
private:
	bool InitializeDX(HWND hwnd, int width, int height);
	bool shaderInitizer();


	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> layoutInput;

	VertexShader vertexShader;
};