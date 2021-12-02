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
	float bGColour[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bGColour);
	
	//** Drawing **//
	this->deviceContext->IASetInputLayout(this->vertexShader.getInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->deviceContext->VSSetShader(vertexShader.getShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixel.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	this->deviceContext->Draw(3, 0);
	
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

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
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
		ErrorLogger::Log(hr, "Failed to create rende target view.");
		return false;
	}

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);

	//** Create the Viewport **//
	D3D11_VIEWPORT viewP;
	ZeroMemory(&viewP, sizeof(D3D11_VIEWPORT));

	viewP.TopLeftX = 0;
	viewP.TopLeftY = 0;
	viewP.Width = 800;
	viewP.Height = 600;

	// Set the Viewport
	this->deviceContext->RSSetViewports(1, &viewP);

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
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
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
		Vertex(0.0f, -0.2f),
		Vertex(-0.1f, 0.0f),
		Vertex(0.1f, 0.0f),
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

	return true;
}
