#pragma once

/* Stores an OpenGL texture as an object */
class GLTexture
{
public:
	GLTexture(unsigned int textureID) : textureID(textureID) {}
	/* Returns the ID of the texture */
	unsigned int getTextureID() { return textureID; };
private:
	/* The OpenGL's texture ID */
	unsigned int textureID;
};