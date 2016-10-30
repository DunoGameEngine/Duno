#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "DunoWidget.h"
using namespace std;

namespace DunoGUI
{
	class DunoWindow
	{
	public:
		DunoWindow(unsigned int width, unsigned int height, string title = "DunoWindow"): 
			m_width(width),
			m_height(height),
			m_title(title) {};

		/* Set Up WinAPI Window */
		void initWindow();

		/* Add A New Widget */
		void addWidget(DunoWidget* widget) { m_widgets.push_back(widget); }
	private:
		/* Window's Window Object */
		HWND m_window;

		/* Window Title */
		string m_title;

		/* Window Size */
		unsigned int m_width, m_height;

		/* Windows Message CallBack */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		/* List Of Widgets To Render */
		static vector<DunoWidget*> m_widgets;
	};
}