#pragma once
#include "MouseEvent.h"
#include <queue>
using namespace std;
//
//class MouseClass
//{
//public:
//	void onLPress(int x, int y);
//	void onLRelease(int x, int y);
//	void onRPress(int x, int y);
//	void onRRelease (int x, int y);
//	void onMPress(int x, int y);
//	void onMRelease (int x, int y);
//	void onWheelUp(int x, int y);
//	void onWheelDown(int x, int y);
//
//	bool leftDown();
//	bool midDown();
//	bool rightDown();
//
//	int xPos();
//	int yPos();
//	MousePoint getPosition();
//
//	bool bufferEventEmpty();
//	MouseEvent eventRead();
//
//private:
//	queue<MouseEvent> bufferEvent;
//	bool leftDown = false;
//	bool rightDown = false; 
//	bool midMouseDown = false;
//	int x = 0;
//	int y = 0;
//};