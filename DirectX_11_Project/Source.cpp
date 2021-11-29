#include "Engine.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	engine engine;
	engine.initialize(hInstance, "Test", "MyClass", 600, 600);
	while (engine.processMessages() == true)
	{
		engine.update();
	}

	return 0;
}