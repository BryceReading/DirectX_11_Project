#pragma once
#include "ErrorLogger.h"
using namespace std;

class WindowContainer;

class RenderWin
{
public:
	bool initialize(WindowContainer * pwindowContainer, HINSTANCE hInstance, string window_Title, string window_Class, int width, int height);
	bool processMsg();
	HWND GetHWND() const;
	~RenderWin();
private:
	void registerWindowClass();
	HWND handle = NULL;
	HINSTANCE hInstance = NULL;
	string window_Title = "";
	wstring window_Title_Wide = L"";
	string window_Class = "";
	wstring window_Class_wide = L"";
	int width = 0;
	int height = 0;
};