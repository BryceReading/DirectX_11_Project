#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!InitializeDX(hwnd, width, height))
		return false;

	return true;
}

bool Graphics::InitializeDX(HWND hwnd, int width, int height)
{
	vector<AdapterData> adapter = AdapterReader::GetAdapter();

	return true;
}