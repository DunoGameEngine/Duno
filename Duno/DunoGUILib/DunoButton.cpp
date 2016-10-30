#include "DunoButton.h"
#include "TypeLib.h"
#include "DunoGUI.h"
#include <iostream>
using namespace DunoGUI;
using namespace std;

DunoButton::DunoButton(DunoLayout* layout, string text, unsigned int width, unsigned int height):
	DunoWidget("button")
{
	m_text = strToWinStr(text);
	m_has_on_click = false;
	m_buttonID = currentID++;

	unsigned int x, y;
	layout->getNextPosition(&x, &y, width, height);
	init(x, y, width, height);
}

/* Create Widget Objects */
void DunoButton::createWidget(HWND& hWnd)
{
	/* Create The WinAPI Button */
	m_button = CreateWindow(L"button", m_text.c_str(),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		getX(), getY(),
		getWidth(), getHeight(),
		hWnd, (HMENU)m_buttonID,
		DunoGUIInsistence::getInstence(), NULL);
}