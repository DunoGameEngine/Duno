#pragma once
#include "DunoWidget.h"
#include "DunoLayout.h"
#include <functional>
using namespace std;

/* Start Button IDs At 1001 */
static unsigned int currentID = 1001;

namespace DunoGUI
{
	/* Button Widget */
	class DunoButton : public DunoWidget
	{
	public:
		DunoButton(DunoLayout* layout, string text, unsigned int width, unsigned int height);

		/* Set On Click Function */
		template<typename Func>
		void setOnClick(Func func) { m_on_click = func; m_has_on_click = true; }

		/* Draw Widget To Screen */
		virtual void drawWidget(HDC hdc) {}

		/* Create Widget Objects */
		virtual void createWidget(HWND& hWnd);

		/* Called When Clicked */
		virtual void onClick(WPARAM id) { if (id == m_buttonID) if (m_has_on_click) m_on_click(); }
	private:
		/* Display Text */
		wstring m_text;

		/* ID Of Button */
		unsigned int m_buttonID;

		/* WinAPI Button */
		HWND m_button;

		/* On Click Event */
		function<void()> m_on_click;
		bool m_has_on_click;
	};
}