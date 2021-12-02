#include "..\Engine.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	engine engine;
	if (engine.initialize(hInstance, "Test", "MyClass", 800, 600))
	{
		while (engine.processMessages() == true)
		{
			engine.update();
			engine.frameRender();
		}
	}
	return 0;
}

//** Rendering Pipeline  **//
//** - Input Assembler  **// Completed
//** - Vertex Shader   **//  Completed
//** - Rasterizer     **//	 Completed
//** - Pixel Shader  **//	 Completed
//** - Output Merger *//	 Completed

//** Vertex buffer **//
//**     Draw	  **//

