#include "AdaptorReader.h"

vector<AdapterData> AdapterReader::adaptor;

vector<AdapterData> AdapterReader::GetAdapter()
{
	if (adaptor.size() > 0) // Is already initialized
		return adaptor;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	//** DXGIFactory object creation **//
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}
	
	IDXGIAdapter* pAdaptor;
	UINT index = 0;

	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdaptor)))
	{
		adaptor.push_back(AdapterData(pAdaptor));
		index += 1;
	}

	return adaptor;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdaptor = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->description);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to get descriptiom forIDXGIAdapter");
	}
}