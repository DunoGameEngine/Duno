#pragma once

/* Stores an OpenGL texture as an object */
class GLTexture
{
public:
	GLTexture(unsigned int textureID) : textureID(textureID) {}
	/* Returns the ID of the texture */
	unsigned int getTextureID() { return textureID; };
private:
	/* The opengl's texture ID */
	unsigned int textureID;
};

/* Stores the colection of textures that make up the objects materal */
class GLMaterial
{
public:
	/* Creates a basic mat */
	GLMaterial(GLTexture* defuse) : defuse(defuse), bump(nullptr) {}
	/* Creates a mat with a bump map */
	GLMaterial(GLTexture* defuse, GLTexture* bump) : defuse(defuse), bump(bump) {}
	~GLMaterial() { delete defuse; if (bump != nullptr) delete bump; }
	/* Getters */

	GLTexture* getDefuse() { return defuse; };
	GLTexture* getBump() { return bump; }
private:
	/* Data */

	GLTexture* defuse;
	GLTexture* bump;
};