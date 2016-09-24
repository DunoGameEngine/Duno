#pragma once
#include "Types\GLTexture.h"
#include "../Assets/FileLoader/ImageFile.h"
#include "Types\GLTexture.h"
#include <string>
using namespace std;

class GLTextureLoader
{
public:
	GLTexture* loadTexture(FileType::ImageFile file);
	static void bindTexture(GLTexture* texture, unsigned int place);
	static void deleteTexture(GLTexture* texture);
};