#pragma once

class GLTexture
{
public:
	GLTexture(unsigned int textureID) : textureID(textureID) {}
	unsigned int getTextureID() { return textureID; };
private:
	unsigned int textureID;
};
class GLMateral
{
public:
	GLMateral(GLTexture* defuse) : defuse(defuse), bump(nullptr) {}
	GLMateral(GLTexture* defuse, GLTexture* bump) : defuse(defuse), bump(bump) {}

	GLTexture* getDefuse() { return defuse; };
	GLTexture* getBump() { return bump; }
private:
	GLTexture* defuse;
	GLTexture* bump;
};