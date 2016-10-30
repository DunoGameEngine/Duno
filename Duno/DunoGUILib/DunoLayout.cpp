#include "DunoLayout.h"
#include <cmath>
using namespace DunoGUI;

/* Returns The Next Position */
void DunoLayout::getNextPosition(unsigned int* x, unsigned int* y, unsigned int width, unsigned int height)
{
	/* Return position in buffer */
	*x = m_buffer_x;
	*y = m_buffer_y;
	
	/* If horizontal mode, then increase the x buffer */
	if (m_layout_type == DUNOLAYOUT_HORZ)
	{
		m_buffer_x += width + m_padding;
		m_buffer_ext = (unsigned int)fmaxf((float)height, (float)m_buffer_ext);
	}
	/* If vertical mode, then increase the y buffer */
	else if (m_layout_type == DUNOLAYOUT_VERT)
	{
		m_buffer_y += height + m_padding;
		m_buffer_ext = (unsigned int)fmaxf((float)width, (float)m_buffer_ext);
	}

	/* Calculate total window width and height */
	m_window_width = (unsigned int)fmaxf((float)m_buffer_x, (float)m_window_width);
	m_window_height = (unsigned int)fmaxf((float)m_buffer_y, (float)m_window_height);
}

void DunoLayout::nextLine()
{
	/* If horizontal mode, then increase the y buffer */
	if (m_layout_type == DUNOLAYOUT_HORZ)
	{
		m_buffer_x = m_padding;
		m_buffer_y += m_buffer_ext + m_padding;
	}
	/* If vertical mode, then increase the x buffer */
	else if (m_layout_type == DUNOLAYOUT_VERT)
	{
		m_buffer_x += m_buffer_ext + m_padding;
		m_buffer_y = m_padding;
	}

	/* Reset Extent Buffer */
	m_buffer_ext = m_padding;
}