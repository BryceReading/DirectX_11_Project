#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
		this->keyStates[i] = false;  // Intialize all key states to off [false]
}

bool KeyboardClass::keyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool KeyboardClass::keyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool KeyboardClass::charBufferIsEmpty()
{
	return this->charBuffer.empty();
}

KeyboardEvent KeyboardClass::readKey()
{
	if (this->keyBuffer.empty()) // If no key is read return empty event
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = this->keyBuffer.front(); // Gets first keyboard event from queue
		this->keyBuffer.pop(); // Remove first item from the queue
		return e;
	}
}

unsigned char KeyboardClass::readChar()
{
	if (this->keyBuffer.empty()) // If no key is read return empty event
	{
		return 0u; 
	}
	else
	{
		unsigned char e = this->charBuffer.front(); // Gets first keyboard event from queue
		this->charBuffer.pop(); // Remove first item from the queue
		return e;
	}
}

void KeyboardClass::onKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::onKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));

}

void KeyboardClass::onChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void KeyboardClass::enableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}

void KeyboardClass::disableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}

void KeyboardClass::enableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}

void KeyboardClass::disableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}

bool KeyboardClass::isKeysAutoRepeat()
{
	return this->autoRepeatKeys;
}

bool KeyboardClass::isCharsAutoRepeat()
{
	return this->autoRepeatChars;
}
