#pragma once
#include "..\\ErrorLogger.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#include <wrl/client.h>
#include <vector>

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdaptor);
	IDXGIAdapter* pAdaptor = nullptr;
	DXGI_ADAPTER_DESC description;
};

class AdapterReader
{
public:
	static vector<AdapterData> GetAdapter();

private:
	static vector<AdapterData> adaptor;
};