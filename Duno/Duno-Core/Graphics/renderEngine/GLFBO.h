#pragma once
#include "Types/GLTexture.h"

/*                                      */
/*                                      */
/*                UNUSED                */
/*                                      */
/*                                      */

class GLFBO
{
public:
	GLFBO(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height) { initFrameBuffer(); }
	void bindFrameBuffer();
	void unbind();

	GLTexture* getTexture() { return new GLTexture(m_texture); }
private:
	void initFrameBuffer();

	unsigned int m_width, m_height;
	unsigned int m_frame_buffer;
	unsigned int m_texture;
	unsigned int m_depth_buffer;
};