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

	const float camSpeed = 0.02f;

	if (keyboard.keyIsPressed('W'))
	{
		this->gfx.cam.positionAdjust(this->gfx.cam.getVectorForward() * camSpeed);
	}
	if (keyboard.keyIsPressed('S'))
	{
		this->gfx.cam.positionAdjust(this->gfx.cam.getVectorBackwards() * camSpeed);
	}
	if (keyboard.keyIsPressed('A'))
	{
		this->gfx.cam.positionAdjust(this->gfx.cam.getVectorLeft() * camSpeed);
	}
	if (keyboard.keyIsPressed('D'))
	{
		this->gfx.cam.positionAdjust(this->gfx.cam.getVectorRight() * camSpeed);
	}
	if (keyboard.keyIsPressed(VK_SPACE))
	{
		this->gfx.cam.postitinAdjust(0.0f, camSpeed, 0.0f);
	}
	if (keyboard.keyIsPressed('Z'))
	{
		this->gfx.cam.postitinAdjust(0.0f, -camSpeed, 0.0f);
	}
}

void engine::frameRender()
{
	gfx.frameRender();
}
