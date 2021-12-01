#include "..\Graphics\Shaders.h"

bool VertexShader::initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPathway)
{
	HRESULT hr = D3DReadFileToBlob(shaderPathway.c_str(), this->shader_buffer.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderPathway;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	hr = device->CreateVertexShader(this->shader_buffer.Get()->GetBufferPointer(), this->shader_buffer->GetBufferSize(), NULL, this->shader.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to create Vertex shader: ";
		errorMsg += shaderPathway;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}
	
	return true;
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->shader.Get();
}

ID3D10Blob* VertexShader::getBuffer()
{
	return this->shader_buffer.Get();
}
