#include "GLTextureLoader.h"
#include "../Assets/FileLoader/stb_image.h"
#include "../OpenGL/GL.h"
#include "../GameUtil/Logger.h"
#include <iostream>
using namespace std;

void GLTextureLoader::bindTexture(GLTexture* texture, unsigned int place)
{ 
	glActiveTexture(GL_TEXTURE0 + place);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
};
void GLTextureLoader::bindTextureCube(GLTexture* texture, unsigned int place)
{
	glActiveTexture(GL_TEXTURE0 + place);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getTextureID());
};
void GLTextureLoader::deleteTexture(GLTexture* texture) 
{ 
	GLuint textureID = (GLuint)texture->getTextureID(); 
	glDeleteTextures(1, &textureID); 
	delete texture;
}

GLTexture* GLTextureLoader::loadTexture(FileType::ImageFile file)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(file.getURL().c_str(), &width, &height, &numComponents, 4);
	if (imageData == NULL) {}
		// Do error

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.0F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0/*mipmapping*/, GL_RGBA, width, height, 0/*border*/, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
	return new GLTexture(texture);
}

GLTexture* GLTextureLoader::loadCubeMap(FileType::File path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	string images[] = { "posx.png", "negx.png", "posy.png", "negy.png", "posz.png", "negz.png" };
	int width, height, numComponents;
	unsigned char* imageData;
	for (unsigned int i = 0; i < 6; i++)
	{
		imageData = stbi_load((path.getURL() + images[i]).c_str(), &width, &height, &numComponents, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

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