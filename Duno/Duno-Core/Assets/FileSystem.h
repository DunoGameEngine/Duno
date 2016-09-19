#pragma once
#include <string>
using namespace std;

namespace FileType
{
	/* Represents an unkown file type */
	class File
	{
	public:
		/* Sets the url of the file by defalt */
		File(string url) : url_(url) {}
		/* Loads the data of the file to a string */
		void loadFileData();

		/* Getters */
		string getURL() { return url_; }
		string getData() { return data_; };
	private:
		/* URL of the file */
		string url_;
		/* Stores the contents of the file */
		string data_;
	};
}

/* Manegers the asset file system */
class FileSystem
{
public:
	/* Sets the asset home dir */
	static void setHome(string home);
	/* Returns a file */
	static File getFile(string url);
	/* Returns and loads a file */
	static File loadFile(string url);
private:
	/* Stores the home dir */
	static string home_;
};