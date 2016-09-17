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
OBJFile* OBJFile::operator<<(File& file)
{
	Logger::setSpace("OBJLoader");
	// Some vectors of data
	vector<Virtex*> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;
	vector<unsigned int> indices;

	ifstream f(file.getURL());
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
				Virtex* virtex = vertices.at(v - 1);
				if (!virtex->isSet())
				{
					virtex->textureIndex = t - 1;
					virtex->normalIndex = n - 1;
					indices.push_back(v - 1);
				}
				else
				{
					/* Deal with duplecate vertices */
					bool done = false;
					while (!done)
					{
						done = true;
						if (virtex->textureIndex == t - 1 && virtex->normalIndex == n - 1)
							indices.push_back(virtex->index);
						Virtex* dup = virtex->dup;
						if (dup != NULL)
							done = false; virtex = dup; continue;
						Virtex* duplicateVertex = new Virtex((unsigned int)vertices.size(), virtex->position);
						duplicateVertex->textureIndex = t - 1;
						duplicateVertex->normalIndex = n - 1;
						virtex->dup = duplicateVertex;
						vertices.push_back(duplicateVertex);
						indices.push_back(virtex->index);
					}
					cout << "====================" << endl;
				}
			}
		}
		else
		{
			throw new WrongFileTypeExcption("OBJFile");
		}
	}

	/* Convert data to arrays */
	postionSize_ = (unsigned int)vertices.size() * 3;
	textureSize_ = (unsigned int)vertices.size() * 2;
	normalSize_  = (unsigned int)vertices.size() * 3;
	positionArray_ = new float[postionSize_];
	textureArray_  = new float[textureSize_];
	normalArray_   = new float[normalSize_];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		Virtex* virtex = vertices[i];
		glm::vec3 position = virtex->position;
		glm::vec2 texture = textures.at(virtex->textureIndex);
		glm::vec3 normal = normals.at(virtex->normalIndex);
		positionArray_[i * 3] = position.x;
		positionArray_[(i * 3) + 1] = position.y;
		positionArray_[(i * 3) + 2] = position.z;
		textureArray_[i * 2] = texture.x;
		textureArray_[(i * 2) + 1] = texture.y;
		normalArray_[i * 3] = normal.x;
		normalArray_[(i * 3) + 1] = normal.y;
		normalArray_[(i * 3) + 2] = normal.z;
	}
	indecesSize_ = (unsigned int)indices.size();
	indicesArray_ = &indices[0];
	for (Virtex* virtex : vertices) delete virtex;
	Logger::logln(("Loaded OBJFile " + file.getURL()).c_str());
	Logger::back();
	return this;
}