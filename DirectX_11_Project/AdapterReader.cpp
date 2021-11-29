#include "AdaptorReader.h"

vector<AdapterData> AdapterReader::adaptor;

vector<AdapterData> AdapterReader::GetAdapterData()
{
	if (adaptor.size() > 0) // Is already initialized
		return adaptor;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	//** DXGIFactory object creation **//
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
	}
}