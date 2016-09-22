#pragma once
#include "../FileSystem.h"

namespace FileType
{
	class ImageFile : public File
	{
	public:
		ImageFile(File file) : File(file) {}
		static ImageFile load(File file);
	};
}