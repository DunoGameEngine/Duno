#include "../Assets/FileLoader/stb_image.h"
#include "../OpenGL/GL.h"
#include "../GameUtil/Logger.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

/* Binds a texture to a position */
void GLTextureLoader::bindTexture(GLTexture* texture, unsigned int place)
{ 
	glActiveTexture(GL_TEXTURE0 + place);
	if (texture != nullptr)
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	else
		glBindTexture(GL_TEXTURE_2D, 0);
};

/* Binds a cube map to a position */
void GLTextureLoader::bindTextureCube(GLTexture* texture, unsigned int place)
{
	glActiveTexture(GL_TEXTURE0 + place);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getTextureID());
};

/* Converts an image file to an OpenGL texture */
GLTexture* GLTextureLoader::loadTexture(FileType::ImageFile file)
{
	/* Read the data from the file */
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(file.getURL().c_str(), &width, &height, &numComponents, 4);
	if (imageData == NULL) {}
		// Do error

	/* Create an OpenGL texture */
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Set the texture params */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.0F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Load the image's data to the texture */
	glTexImage2D(GL_TEXTURE_2D, 0/*mipmapping*/, GL_RGBA, width, height, 0/*border*/, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	/* Free the image's data */
	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
	return new GLTexture(texture);
}

/* Loads six textures into a cube map */
GLTexture* GLTextureLoader::loadCubeMap(FileType::File path)
{
	/* Create an OpenGL cube map */
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	/* Define the names of the six images */
	string images[] = { "posx.png", "negx.png", "posy.png", "negy.png", "posz.png", "negz.png" };
	
	/* Load each texture */
	int width, height, numComponents;
	unsigned char* imageData;
	for (unsigned int i = 0; i < 6; i++)
	{
		imageData = stbi_load((path.getURL() + images[i]).c_str(), &width, &height, &numComponents, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	/* Set the texture params */
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_LOD_BIAS, -2.0F);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 20);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return new GLTexture(texture);
}

/* Deletes the texture */
void GLTextureLoader::deleteTexture(GLTexture* texture) 
{ 
	GLuint textureID = (GLuint)texture->getTextureID(); 
	glDeleteTextures(1, &textureID); 
	delete texture;
}