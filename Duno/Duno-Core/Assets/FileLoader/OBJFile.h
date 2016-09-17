#pragma once
#include "../FileSystem.h"
#include <iostream>
using namespace std;

/* An OBJ file */
class OBJFile : public File
{
public:
	/* Default constructor */
	OBJFile() : File("") {}
	/* Converts a normal file to an obj file */
	static OBJFile* load(File& file);
	~OBJFile() { delete[] positionArray_; delete[] textureArray_; delete[] normalArray_; delete[] indicesArray_; }
private:
	/* OBJ data */
	unsigned int postionSize_;
	unsigned int textureSize_;
	unsigned int normalSize_;
	unsigned int indecesSize_;

	float* positionArray_;
	float* textureArray_;
	float* normalArray_;
	unsigned int* indicesArray_;
};