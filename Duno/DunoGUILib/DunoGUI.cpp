#include "DunoGUI.h"
#include <tchar.h>
using namespace DunoGUI;

HINSTANCE DunoGUIInsistence::m_instance;
HINSTANCE DunoGUIInsistence::m_prev_instance;
LPSTR DunoGUIInsistence::m_lp_cmd_line;
int DunoGUIInsistence::m_cmd_show;

/* Initialize Insistence */
void DunoGUIInsistence::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	m_instance = hInstance;
	m_prev_instance = hPrevInstance;
	m_lp_cmd_line = lpCmdLine;
	m_cmd_show = nCmdShow;
}

/* Start Main Loop Running */
int DunoGUIInsistence::startLoop()
{
	/* Message loop to listen for message sent from Windows */
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* Dispatch message to the WinProc loop */
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}