#pragma once
#include "Types\GLTexture.h"
#include "../Assets/FileLoader/ImageFile.h"
#include "Types\GLTexture.h"
#include <string>
using namespace std;

/* Loads the textures from a image file to an OpenGL texture */
class GLTextureLoader
{
public:
	/* Converts an image file to an OpenGL texture */
	GLTexture* loadTexture(FileType::ImageFile file);
	/* Loads six textures into a cube map */
	GLTexture* loadCubeMap(FileType::File path);
	/* Binds a texture to a position */
	static void bindTexture(GLTexture* texture, unsigned int place);
	/* Binds a cube map to a position */
	static void bindTextureCube(GLTexture* texture, unsigned int place);
	/* Delets the texture */
	static void deleteTexture(GLTexture* texture);
};