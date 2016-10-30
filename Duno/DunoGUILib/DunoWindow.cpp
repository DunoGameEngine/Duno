#include "DunoWindow.h"
#include "DunoError.h"
#include "TypeLib.h"
#include "DunoGUI.h"
#include <tchar.h>
using namespace DunoGUI;

vector<DunoWidget*> DunoWindow::m_widgets;

/* The main window class name */
static TCHAR szWindowClass[] = _T("win32app");

void DunoWindow::initWindow()
{
	/* Window Information */
	WNDCLASSEX wcex;

	/* Set Default Window Information */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = DunoGUIInsistence::getInstence();
	wcex.hIcon = LoadIcon(DunoGUIInsistence::getInstence(), MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	/* Register the window with Windows */
	if (!RegisterClassEx(&wcex))
		DunoError::out(_T("Unable to register window"));

	/* Create the window */
	HWND hWnd = CreateWindow(
		szWindowClass,
		strToWinStr(m_title).c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_width, m_height,
		NULL,
		NULL,
		DunoGUIInsistence::getInstence(),
		NULL
		);
	/* Error check */
	if (!hWnd)
		DunoError::out(_T("Unable to create window"));

	/* Display the window on screen */
	ShowWindow(hWnd, DunoGUIInsistence::getCMDShow());
	UpdateWindow(hWnd);
}

/* Windows Message CallBack */
LRESULT CALLBACK DunoWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		/* Create all widgets */
		for (DunoWidget* widget : m_widgets)
			widget->createWidget(hWnd);
		break;
	case WM_COMMAND:
		/* Update All Widgets */
		for (DunoWidget* widget : m_widgets)
			widget->onClick(wParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(240, 240, 240));

		/* Draw All Widgets */
		for (DunoWidget* widget : m_widgets)
			widget->drawWidget(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}