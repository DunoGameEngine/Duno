#pragma once
#include "../FileSystem.h"

namespace FileType
{
	/* Stores Data For An Image */
	class ImageFile : public File
	{
	public:
		ImageFile(File file) : File(file) {}
		/* Loads Data From File */
		static ImageFile load(File file);
	};
}