#pragma once
#include "RenderWin.h"
#include "Keyboard/KeyboardClass.h"
#include "Graphics\Graphics.h"

class WindowContainer
{
public:
	WindowContainer();
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	RenderWin render_Win;
	KeyboardClass keyboard;

	Graphics gfx;
private:
};