#include "Engine.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	engine E;
	E.initialize(hInstance, "Test", "MyClass", 600, 600);
	while (E.processMessages() == true)
	{
	}

	return 0;
}