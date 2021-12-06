#pragma once
#include "Exeption.h"
#include <Windows.h>
using namespace std;

class ErrorLogger
{
public: 
	static void Log(string message);
	static void Log(HRESULT hr, string message);
	static void Log(HRESULT hr, wstring message);
	static void Log(Exceptions & exception);
};