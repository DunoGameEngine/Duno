#pragma once
#include <string>
#include <Windows.h>
using namespace std;

namespace DunoGUI
{
	/* Generic Widget Object */
	class DunoWidget
	{
	public:
		DunoWidget(string name): m_name(name) {}
		void init(unsigned int x, unsigned int y, unsigned int width, unsigned int height) { m_x = x; m_y = y; m_width = width; m_height = height; }

		/* Draw Widget To Screen */
		virtual void drawWidget(HDC hdc) = 0;

		/* Create Widget Objects */
		virtual void createWidget(HWND& hWnd) = 0;

		/* Called When Clicked */
		virtual void onClick(WPARAM id) = 0;
	protected:
		/* Get X Position */
		unsigned int getX() { return m_x; }

		/* Get Y Position */
		unsigned int getY() { return m_y; }

		/* Get Width */
		unsigned int getWidth() { return m_width; }

		/* Get Height */
		unsigned int getHeight() { return m_height; }
	private:
		/* Name Of Widget Type */
		string m_name;

		/* Position On Screen */
		unsigned int m_x, m_y;

		/* Size On Screen */
		unsigned int m_width, m_height;
	};
}