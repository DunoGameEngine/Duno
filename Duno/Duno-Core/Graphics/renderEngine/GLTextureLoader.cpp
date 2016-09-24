#include "GLTextureLoader.h"
#include "../Assets/FileLoader/stb_image.h"
#include "../OpenGL/GL.h"

void GLTextureLoader::bindTexture(GLTexture* texture, unsigned int place)
{ 
	glActiveTexture(GL_TEXTURE0 + place);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID()); 
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