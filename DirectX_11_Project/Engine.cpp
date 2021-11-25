#include "Engine.h"

bool engine::initialize(HINSTANCE hInstance, string window_Title, string window_Class, int width, int height)
{
	return this->render_Win.initialize(this, hInstance,window_Title, window_Class, width, height);
	
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
		string outMsg = "Char: ";
		outMsg += ch;
		outMsg += "\n";
		OutputDebugStringA(outMsg.c_str());
	}

	// continue from 11.01 in vid 5 
}
