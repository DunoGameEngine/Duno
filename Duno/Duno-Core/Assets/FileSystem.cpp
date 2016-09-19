#include "FileSystem.h"
#include <fstream>
#include <streambuf>

/* File */
void FileType::File::loadFileData()
{
	std::ifstream t(url_);
	data_ = string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();
}

/* File System */
string FileSystem::home_;
void FileSystem::setHome(string home)
{
	home_ = home;
}
FileType::File FileSystem::getFile(string url)
{
	return FileType::File(home_ + url);
}
FileType::File FileSystem::loadFile(string url)
{
	FileType::File file = getFile(url);
	file.loadFileData();
	return file;
}