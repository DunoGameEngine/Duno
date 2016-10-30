#pragma once
#include <Windows.h>
#include <string>
using namespace std;

namespace DunoGUI
{
	/* Converts Normal String To A WinAPI One */
	wstring strToWinStr(string s);
}