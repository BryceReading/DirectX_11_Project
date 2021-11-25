#include "ConverString.h"
using namespace std;

wstring Converter::stringToWide(string str)
{
	wstring wide_string(str.begin(), str.end());
	return wide_string;
}
