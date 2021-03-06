#include "..\Graphics\Shaders.h"

bool VertexShader::initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPathway, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT elementNum)
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
	
	hr= device->CreateInputLayout(layoutDesc, elementNum, this->shader_buffer->GetBufferPointer(), this->shader_buffer->GetBufferSize(), this->inputLayout.GetAddressOf());

	// Checking for any Errors
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create rende target view.");
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

ID3D11InputLayout* VertexShader::getInputLayout()
{
	return this->inputLayout.Get();
}

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderPath)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), this->shader_buffer.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderPath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	hr = device->CreatePixelShader(this->shader_buffer.Get()->GetBufferPointer(), this->shader_buffer.Get()->GetBufferSize(), NULL, this->shader.GetAddressOf());
	if (FAILED(hr))
	{
		wstring errorMsg = L"Failed to create pixel shader: ";
		errorMsg += shaderPath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return this->shader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return this->shader_buffer.Get();
}
