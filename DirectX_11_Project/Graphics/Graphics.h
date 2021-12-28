#pragma once
#include "AdaptorReader.h"
#include "Shaders.h"
#include "Vertex.h"
#include <WICTextureLoader.h>
#include "Indexbuffer.h"
#include "ConstantBufferTypes.h"
#include "ConstantBuffer.h"

class Graphics
{
public:
	bool Initialize(HWND hWnd, int width, int height);
	void frameRender();
private:
	bool InitializeDX(HWND hwnd);
	bool shaderInitizer();
	bool sceneInitizer();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	VertexShader vertexShader;
	PixelShader pixel;
	ConstantBuffer<CB_VS_vertexShader> constBuffer;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer2;

	IndexBuffer bufferIndices;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthSV;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>depthSB;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthSS;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	int windWidth = 0;
	int windHeight = 0;
};