#pragma once
#include <comdef.h>
#include "ConverString.h"

#define COM_ERROR_IF_FAILED(hr, msg) if(FAILED(hr)) throw Exeption(hr, msg, __FILE__, __FUNCTION__, __LINE__)

class Exceptions
{
public:
	Exceptions(HRESULT hr, const string& msg, const string& file, const string& function, int line)
	{
		_com_error error(hr);
		whatmsg = L"Msg: " + Converter::stringToWide(string(msg)) + L"\n";
		whatmsg += error.ErrorMessage();
		whatmsg += L"\nFile: " + Converter::stringToWide(file);
		whatmsg += L"\nFunction: " + Converter::stringToWide(function);
		whatmsg += L"\nLine: " + Converter::stringToWide(to_string(line));
	}
	const wchar_t* what() const
	{
		return whatmsg.c_str();
	}
private:
	wstring whatmsg;
};