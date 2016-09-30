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
		normalIndex(-1),
		dup(NULL),
		tangent(glm::vec3()) {};
	bool isSet() { return textureIndex != -1 && normalIndex != -1; }
	unsigned int index;
	unsigned int textureIndex;
	unsigned int normalIndex;
	glm::vec3 position;
	glm::vec3 tangent;
	Virtex* dup;
};
Virtex* dealWithAlreadyProcessedVertex(Virtex* preVirtex, int v, int t, int n, vector<unsigned int>& indecies, vector<Virtex*>& vertices)
{
	if (preVirtex->textureIndex == t - 1 && preVirtex->normalIndex == n - 1)
	{
		indecies.push_back(preVirtex->index);
		return preVirtex;
	}
	else
	{
		Virtex* anoutherVirtex = preVirtex->dup;
		if (anoutherVirtex != NULL)
			return dealWithAlreadyProcessedVertex(anoutherVirtex, v, t, n, indecies, vertices);
		else
		{
			Virtex* dupVirtex = new Virtex(vertices.size(), preVirtex->position);
			dupVirtex->textureIndex = t - 1;
			dupVirtex->normalIndex = n - 1;
			preVirtex->dup = dupVirtex;
			vertices.push_back(dupVirtex);
			indecies.push_back(dupVirtex->index);
			return dupVirtex;
		}
	}
}
Virtex* prossesVertex(int v, int t, int n, vector<Virtex*>& vertices, vector<unsigned int>& indecies)
{
	Virtex* currentVirtex = vertices[v - 1];
	if (!currentVirtex->isSet())
	{
		currentVirtex->textureIndex = t - 1;
		currentVirtex->normalIndex = n - 1;
		indecies.push_back(v - 1);
		return currentVirtex;
	}
	else
	{
		if (currentVirtex != NULL)
			return dealWithAlreadyProcessedVertex(currentVirtex, v, t, n, indecies, vertices);
	}
}
/* Convert File to OBJFile (only temp) */
FileType::OBJFile FileType::OBJFile::load(File& file, bool useTangents)
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
			Virtex* virt[3];
			for (unsigned int i = 0; i < 3; i++)
			{
				int v, t, n; iss >> v >> t >> n;
				virt[i] = prossesVertex(v, t, n, vertices, indices);
			}
			glm::vec2 uv0 = textures[virt[0]->textureIndex];
			glm::vec2 deltaUv1 = textures[virt[1]->textureIndex] - uv0;
			glm::vec2 deltaUv2 = textures[virt[2]->textureIndex] - uv0;

			glm::vec3 tangent = (((virt[1]->position - virt[0]->position) * deltaUv2.y) - ((virt[2]->position - virt[0]->position) * deltaUv1.y)) *
				(1.0F / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
			virt[0]->tangent = tangent;
			virt[1]->tangent = tangent;
			virt[2]->tangent = tangent;
		}
		else
		{
			if (!(type == "s" || type == "o" || type == "#"))
				throw new WrongFileTypeExcption("OBJFile");
		}
	}

	/* Convert data to arrays */
	vector<float> positionArray = vector<float>(indices.size() * 3);
	vector<float> textureArray  = vector<float>(indices.size() * 2);
	vector<float> normalArray   = vector<float>(indices.size() * 3);
	vector<float> tangentArray = vector<float>(indices.size() * 3);
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		Virtex* virtex = vertices[i];
		glm::vec3 position = virtex->position;
		glm::vec2 texture = textures[virtex->textureIndex];
		glm::vec3 normal = normals[virtex->normalIndex];
		glm::vec3 tangent = virtex->tangent;
		tangentArray[i * 3] = tangent.x;
		tangentArray[(i * 3) + 1] = tangent.y;
		tangentArray[(i * 3) + 2] = tangent.z;
		positionArray[i * 3] = position.x;
		positionArray[(i * 3) + 1] = position.y;
		positionArray[(i * 3) + 2] = position.z;
		textureArray[i * 2] = texture.x;
		textureArray[(i * 2) + 1] = texture.y;
		normalArray[i * 3] = normal.x;
		normalArray[(i * 3) + 1] = normal.y;
		normalArray[(i * 3) + 2] = normal.z;
	}
	for (Virtex* virtex : vertices) delete virtex;

	ModelInfo* info = new ModelInfo();
	info->positions = positionArray;
	info->textures = textureArray;
	info->normals = normalArray;
	info->indices = indices;
	info->useTangents = useTangents;
	info->tangents = tangentArray;
	Logger::logln(("Loaded OBJFile " + file.getURL()).c_str());
	Logger::back();
	return OBJFile(file, info);
}