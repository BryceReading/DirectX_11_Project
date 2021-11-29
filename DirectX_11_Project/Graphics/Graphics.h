#pragma once
#include "AdaptorReader.h"
class Graphics
{
public:
	bool Initialize(HWND hWnd, int width, int height);

private:
	bool InitializeDX(HWND hwnd, int width, int height);

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
};