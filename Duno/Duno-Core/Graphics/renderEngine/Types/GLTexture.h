#pragma once
#include "../OpenGL/GL.h"

class GLTexture
{
public:
	GLTexture(GLuint textureID) : textureID(textureID) {}
	void bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
	~GLTexture() { glDeleteTextures(1, &textureID); }
private:
	GLuint textureID;
};