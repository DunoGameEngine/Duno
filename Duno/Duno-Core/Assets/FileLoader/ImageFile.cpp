#include "ImageFile.h"

FileType::ImageFile FileType::ImageFile::load(FileType::File file)
{
	return ImageFile(file);
}