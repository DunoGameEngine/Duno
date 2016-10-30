#pragma once
#include "DunoWidget.h"

namespace DunoGUI
{
	/* Label Widget */
	class DunoLabel : public DunoWidget
	{
	public:
		DunoLabel(string text);

		/* Draw Widget To Screen */
		virtual void drawWidget(HDC hdc);

		/* Create Widget Objects */
		void createWidget(HWND& hWnd) {}
	private:
		/* Text Of Label */
		wstring m_text;
	};
}