#include "DunoLabel.h"
#include "TypeLib.h"
#include <tchar.h>
#include <iostream>
using namespace DunoGUI;
using namespace std;

DunoLabel::DunoLabel(string text): DunoWidget("label")
{
	m_text = strToWinStr(text);
	/* TODO: Size and layout calculations */

	init(0, 0, 0, 0);
}

void DunoLabel::drawWidget(HDC hdc)
{
	/* Render Text */
	TextOut(hdc, getX(), getY(), m_text.c_str(), (int)_tcslen(m_text.c_str()));
}