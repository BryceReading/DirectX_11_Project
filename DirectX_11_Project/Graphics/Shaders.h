#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include "..\\ErrorLogger.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

class VertexShader
{
public:
	bool initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPathway);
	ID3D11VertexShader* getShader();
	ID3D10Blob* getBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer = nullptr;
};