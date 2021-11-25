#pragma once
#include "RenderWin.h"
#include "Keyboard/KeyboardClass.h"

class WindowContainer
{
public:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	RenderWin render_Win;
	KeyboardClass keyboard;
private:
};