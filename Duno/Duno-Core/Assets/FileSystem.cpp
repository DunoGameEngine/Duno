#include "FileSystem.h"
#include <fstream>
#include <streambuf>

/* File */
void File::loadFileData()
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
File FileSystem::getFile(string url)
{
	return File(home_ + url);
}
File FileSystem::loadFile(string url)
{
	File file = getFile(url);
	file.loadFileData();
	return file;
}