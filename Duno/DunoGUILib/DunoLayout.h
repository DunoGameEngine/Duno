#pragma once

/* Layout Types */
#define DUNOLAYOUT_VERT 0
#define DUNOLAYOUT_HORZ 1

namespace DunoGUI
{
	/* Calculates Where To Place Widget Next */
	class DunoLayout
	{
	public:
		DunoLayout(unsigned int type, unsigned int padding): 
			m_layout_type(type), m_padding(padding), 
			m_buffer_x(padding), m_buffer_y(padding), m_buffer_ext(padding),
			m_window_width(0), m_window_height(0) {};

		/* Getters */
		unsigned int getWindowWidth() { return m_window_width + m_padding; }
		unsigned int getWindowHeight() { return m_window_height + m_padding; }

		/* Moves Onto The Next Line With No Overlap */
		void nextLine();
		
		/* Returns The Next Position */
		void getNextPosition(unsigned int* x, unsigned int* y, unsigned int width, unsigned int height);
	private:
		/* The Type Of Layout */
		unsigned int m_layout_type;
		
		/* Position Buffers */
		unsigned int m_buffer_x, m_buffer_y;
		unsigned int m_buffer_ext;

		/* Layout Data */
		unsigned int m_window_width, m_window_height;
		unsigned int m_padding;
	};
}