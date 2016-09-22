#pragma once
#include "Types\GLTexture.h"
#include "../Assets/FileLoader/ImageFile.h"
#include <string>
using namespace std;

class GLTextureLoader
{
public:
	GLTexture* loadTexture(FileType::ImageFile file);
};