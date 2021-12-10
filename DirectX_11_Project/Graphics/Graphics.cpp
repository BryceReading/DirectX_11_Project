#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!InitializeDX(hwnd, width, height))
		return false;

	if (!shaderInitizer())
		return false;

	if (!sceneInitizer())
		return false;

	return true;
}

void Graphics::frameRender()
{
	float bGColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bGColour);
	this->deviceContext->ClearDepthStencilView(this->depthSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	
	//** Drawing **//
	this->deviceContext->IASetInputLayout(this->vertexShader.getInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->deviceContext->RSSetState(this->rasterState.Get());

	this->deviceContext->OMSetDepthStencilState(this->depthSS.Get(), 0);
	this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());

	this->deviceContext->VSSetShader(vertexShader.getShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixel.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Iner Triangle
	this->deviceContext->PSSetShaderResources(0, 1, this->texture.GetAddressOf());
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer2.GetAddressOf(), &stride, &offset);
	this->deviceContext->IASetIndexBuffer(bufferIndices.Get(), DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->DrawIndexed(6, 0, 0);


	// Outer Triangle
	this->deviceContext->PSSetShaderResources(0, 1, this->texture.GetAddressOf());
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	this->deviceContext->IASetIndexBuffer(bufferIndices.Get(), DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->DrawIndexed(6, 0, 0);
	
	this->swapChain->Present(1, NULL);
}

bool Graphics::InitializeDX(HWND hwnd, int width, int height)
{
	vector<AdapterData> adapter = AdapterReader::GetAdapter();

	if (adapter.size() < 1)
	{
		ErrorLogger::Log("No IDXGI Adapters found.");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr =  D3D11CreateDeviceAndSwapChain(
			adapter[0].pAdaptor, // IDXGI Adapter
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL, // Softwere Driver
			NULL, // Runtime Layers
			NULL, // Feature Levels Array
			0, // Num of Feature Levels in Array 
			D3D11_SDK_VERSION,
			&scd, // Swapchain Description
			this->swapChain.GetAddressOf(),
			this->device.GetAddressOf(),
			NULL,
			this->deviceContext.GetAddressOf());

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create device and swapchain");
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (backBuffer.GetAddressOf()));

	// Checking for any Errors
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Get Buffer Failed.");
		return false;
	}

	hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());

	// Checking for any Errors
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create render target view.");
		return false;
	}

	//** Depth/Stencil Buffer Desc **//
	D3D11_TEXTURE2D_DESC depthSD;
	depthSD.Width = width;
	depthSD.Height = height;
	depthSD.MipLevels = 1;
	depthSD.ArraySize = 1;
	depthSD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthSD.SampleDesc.Count = 1;
	depthSD.SampleDesc.Quality = 0;
	depthSD.Usage = D3D11_USAGE_DEFAULT;
	depthSD.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthSD.CPUAccessFlags = 0;
	depthSD.MiscFlags = 0;

	hr = this->device->CreateTexture2D(&depthSD, NULL, this->depthSB.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil buffer.");
		return false;
	}

	hr = this->device->CreateDepthStencilView(this->depthSB.Get(), NULL, this->depthSV.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil view.");
		return false;
	}

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthSV.Get());

	//** Create a depth stencil state **//
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL; // Replaces pixles if they are less or equal to the new pixles in depth.

	hr = this->device->CreateDepthStencilState(&depthStencilDesc, this->depthSS.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil state.");
		return false;
	}

	//** Create the Viewport **//
	D3D11_VIEWPORT viewP;
	ZeroMemory(&viewP, sizeof(D3D11_VIEWPORT));

	viewP.TopLeftX = 0;
	viewP.TopLeftY = 0;
	viewP.Width = width;
	viewP.Height = height;
	viewP.MinDepth = 0.0f;
	viewP.MaxDepth = 1.0f;

	// Set the Viewport
	this->deviceContext->RSSetViewports(1, &viewP);

	// Rasterizer state created
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	
	hr = this->device->CreateRasterizerState(&rasterDesc, this->rasterState.GetAddressOf());

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create Rasterizer state.");
		return false;
	}

	//** Sampler State **// Does fully work
	D3D11_SAMPLER_DESC sDesc;
	ZeroMemory(&sDesc, sizeof(sDesc));
	sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sDesc.MinLOD = 0;
	sDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = this->device->CreateSamplerState(&sDesc, this->samplerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create Sampler state.");
		return false;
	}

	return true;
}

bool Graphics::shaderInitizer()
{

	wstring shaderFolder = L"";
#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG
	#ifdef _WIN64 // x64
			shaderFolder = L"..\\x64\\Debug\\";
	#else // x86 (Win32)
			shaderFolder = L"..\\Debug\\";
	#endif 
	#else // Release
	#ifdef _WIN64 // x64
			shaderFolder = L"..\\x64\\Release\\";
	#else // x86 (Win32)
			shaderFolder = L"..\\Release\\";
	#endif 
#endif 
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexShader.initialize(this->device, shaderFolder + L"VertexShader.cso", layout, numElements))
		return false;

	if(!pixel.Initialize(this->device, shaderFolder + L"pixelshader.cso"))
		return false;

	return true;
}

bool Graphics::sceneInitizer()
{
	Vertex v[] =
	{ 
		Vertex(-0.9f, -0.5f, 1.0f, 0.0f, 1.0f),
		Vertex(-0.9f,  0.5f, 1.0f, 0.0f, 0.0f),
		Vertex( 0.0f,  0.5f, 1.0f, 1.0f, 0.0f),
		Vertex( 0.0f, -0.5f, 1.0f, 1.0f, 1.0f),
	};

	DWORD indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	D3D11_BUFFER_DESC vertexBuffDesc;
	ZeroMemory(&vertexBuffDesc, sizeof(vertexBuffDesc));

	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags = 0;
	vertexBuffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;

	HRESULT hr = this->device->CreateBuffer(&vertexBuffDesc, &vertexBufferData, this->vertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	//** Index Data **\\ 
	D3D11_BUFFER_DESC indexBuffDesc;
	ZeroMemory(&indexBuffDesc, sizeof(indexBuffDesc));
	indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBuffDesc.ByteWidth = sizeof(DWORD) * ARRAYSIZE(indices);
	indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBuffDesc.CPUAccessFlags = 0;
	indexBuffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	hr = device->CreateBuffer(&indexBuffDesc, &indexData, bufferIndices.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create indices buffer.");
		return hr;
	}

	// Second Triangle 
	Vertex v2[] =
	{
		Vertex( 0.0f, -0.5f, 1.0f, 0.0f, 1.0f),
		Vertex( 0.0f,  0.5f, 1.0f, 0.0f, 0.0f),
		Vertex(-0.9f,  0.5f, 1.0f, 1.0f, 0.0f),
		Vertex(-0.9f, -0.5f, 1.0f, 1.0f, 1.0f),
	};

		DWORD indices2[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	ZeroMemory(&vertexBuffDesc, sizeof(vertexBuffDesc));

	vertexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBuffDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v2);
	vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffDesc.CPUAccessFlags = 0;
	vertexBuffDesc.MiscFlags = 0;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v2;

	hr = this->device->CreateBuffer(&vertexBuffDesc, &vertexBufferData, this->vertexBuffer2.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\Skull.png", nullptr, texture.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create wic texture from file.");
		return false;

	}

	return true;
}
