#pragma once
#include "../FileSystem.h"
#include <iostream>
#include <vector>
using namespace std;

struct ModelInfo
{
	vector<float> positions;
	vector<float> textures;
	vector<float> normals;
	vector<unsigned int> indices;
};
namespace FileType
{
	/* An OBJ file */
	class OBJFile : public File
	{
	public:
		/* Default constructor */
		OBJFile() : File("") {}
		OBJFile(File file, ModelInfo* info) : File(file), info(info) {}
		/* Converts a normal file to an obj file */
		static OBJFile load(File& file);
		~OBJFile() { delete info; }

		/* Returns the models info */
		ModelInfo* getInfo() { return info; }
	private:
		/* OBJ data */
		ModelInfo* info;
	};
}