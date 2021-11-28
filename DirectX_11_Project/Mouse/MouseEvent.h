#pragma once
struct MousePoint
{
	int x; 
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPress, 
		LRelease,
		RPress,
		RRelease, 
		MPress, 
		MRelease,
		WheelUp,
		WheelDown,
		Move, 
		RAW_MOVE, 
		Ivalid
	};
private:
	EventType et;
	int x;
	int y;
};