#pragma once
#include "KeyboardEvent.h"
#include <queue>
using namespace std;

class KeyboardClass
{
public:
	KeyboardClass();
	bool keyIsPressed(const unsigned char keycode);
	bool keyBufferIsEmpty();
	bool charBufferIsEmpty();
	KeyboardEvent readKey();
	unsigned char readChar();
	void onKeyPressed(const unsigned char key);
	void onKeyReleased(const unsigned char key);
	void onChar(const unsigned char key);
	void enableAutoRepeatKeys();
	void disableAutoRepeatKeys();
	void enableAutoRepeatChars();
	void disableAutoRepeatChars();
	bool isKeysAutoRepeat();
	bool isCharsAutoRepeat();

private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];
	queue<KeyboardEvent> keyBuffer;
	queue<unsigned char> charBuffer;
};