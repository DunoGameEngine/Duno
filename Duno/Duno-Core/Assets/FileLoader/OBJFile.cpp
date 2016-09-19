#include "OBJFile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../GameUtil/Logger.h"
#include "glm/glm.hpp"
#include "../GameUtil/Exceptions.h"
using namespace std;

/* Replace all occurrences */
string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

/* Vertex type */
struct Virtex
{
	Virtex(unsigned int index, glm::vec3 position) :
		index(index),
		position(position),
		textureIndex(-1),
		normalIndex(-1) {};
	bool isSet() { return textureIndex != -1 && normalIndex != -1; }
	unsigned int index;
	unsigned int textureIndex;
	unsigned int normalIndex;
	glm::vec3 position;
	Virtex* dup;
};
/* Convert File to OBJFile (only temp) */
FileType::OBJFile* FileType::OBJFile::load(File& file)
{	
	Logger::setSpace("OBJLoader");
	// Some vectors of data
	vector<Virtex*> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;
	vector<unsigned int> indices;

	ifstream f(file.getURL());
	if (!f.good()) throw new FileNotFoundException(file.getURL());
	string line;
	// Load data (positions, textures, normals)
	while (getline(f, line))
	{
		istringstream iss(replaceAll(line, "/", " "));
		string type; iss >> type;
		if (type == "v") /* vertices */
		{
			float x, y, z; iss >> x >> y >> z;
			vertices.push_back(new Virtex((unsigned int)vertices.size(), glm::vec3(x, y, z)));
		}
		else if (type == "vt") /* textures */
		{
			float x, y; iss >> x >> y;
			textures.push_back(glm::vec2(x, y));
		}
		else if (type == "vn") /* normals */
		{
			float x, y, z; iss >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		else if (type == "f") /* faces */
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				int v, t, n; iss >> v >> t >> n;
				Virtex* virtex = vertices[v - 1];
				virtex->textureIndex = t - 1;
				virtex->normalIndex = n - 1;
				indices.push_back(v - 1);
			}
		}
		else
		{
			if (!(type == "s" || type == "o" || type == "#"))
				throw new WrongFileTypeExcption("OBJFile");
		}
	}

	/* Convert data to arrays */
	unsigned int postionSize = (unsigned int)vertices.size() * 3;
	unsigned int textureSize = (unsigned int)vertices.size() * 2;
	unsigned int normalSize  = (unsigned int)vertices.size() * 3;
	float* positionArray = new float[postionSize];
	float* textureArray  = new float[textureSize];
	float* normalArray   = new float[normalSize];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		Virtex* virtex = vertices[i];
		glm::vec3 position = virtex->position;
		glm::vec2 texture = textures.at(virtex->textureIndex);
		glm::vec3 normal = normals.at(virtex->normalIndex);
		positionArray[i * 3] = position.x;
		positionArray[(i * 3) + 1] = position.y;
		positionArray[(i * 3) + 2] = position.z;
		textureArray[i * 2] = texture.x;
		textureArray[(i * 2) + 1] = texture.y;
		normalArray[i * 3] = normal.x;
		normalArray[(i * 3) + 1] = normal.y;
		normalArray[(i * 3) + 2] = normal.z;
	}
	unsigned int indecesSize = (unsigned int)indices.size();
	unsigned int* indicesArray = &indices[0];
	for (Virtex* virtex : vertices) delete virtex;

	OBJFile* outFile = new OBJFile();
	outFile->postionSize_ = postionSize;
	outFile->textureSize_ = textureSize;
	outFile->normalSize_ = normalSize;
	outFile->indecesSize_ = indecesSize;

	outFile->positionArray_ = positionArray;
	outFile->textureArray_ = textureArray;
	outFile->normalArray_ = normalArray;
	outFile->indicesArray_ = indicesArray;
	Logger::logln(("Loaded OBJFile " + file.getURL()).c_str());
	Logger::back();
	return outFile;
}