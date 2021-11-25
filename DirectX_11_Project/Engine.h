#pragma once
#include "WindowContainer.h"
class engine : WindowContainer
{
public:
	bool initialize(HINSTANCE hInstance, string window_Title, string window_Class, int width, int height);
	bool processMessages();
	void update();

};