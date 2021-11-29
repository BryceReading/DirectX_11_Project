#include "Engine.h"

bool engine::initialize(HINSTANCE hInstance, string window_Title, string window_Class, int width, int height)
{
	if(!this->render_Win.initialize(this, hInstance,window_Title, window_Class, width, height))
		return false;
	if (!gfx.Initialize(this->render_Win.GetHWND(), width, height))
		return false;

	return true;
}

bool engine::processMessages()
{
	return this->render_Win.processMsg();
}

void engine::update()
{
	while (!keyboard.charBufferIsEmpty())
	{
		unsigned char ch = keyboard.readChar();
	}

	while (!keyboard.keyBufferIsEmpty())
	{
		KeyboardEvent event = keyboard.readKey();
		unsigned char keyCode = event.getKeyCoad();
	}
}
