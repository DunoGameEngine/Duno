#pragma once
#include "Types/GLTexture.h"

class GLFBO
{
public:
	GLFBO(unsigned int width, unsigned int height) :
		width(width),
		height(height) { initFrameBuffer(); }
	void bindFrameBuffer();
	void unbind();

	GLTexture* getTexture() { return new GLTexture(texture); }
private:
	void initFrameBuffer();

	unsigned int width, height;
	unsigned int frameBuffer;
	unsigned int texture;
	unsigned int depthBuffer;
};