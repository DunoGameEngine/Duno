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
struct Vertex
{
	Vertex(unsigned int index, glm::vec3 position) :
		index(index),
		position(position),
		textureIndex(0),
		normalIndex(0),
		dup(NULL),
		tangent(glm::vec3()) {};
	bool isSet() { return textureIndex != -1 && normalIndex != -1; }
	unsigned int index;
	unsigned int textureIndex;
	unsigned int normalIndex;
	glm::vec3 position;
	glm::vec3 tangent;
	Vertex* dup;
};
inline Vertex* dealWithAlreadyProcessedVertex(Vertex* perVertex, int v, int t, int n, vector<unsigned int>& indecies, vector<Vertex*>& vertices)
{
	if (perVertex->textureIndex == t - 1 && perVertex->normalIndex == n - 1)
	{
		indecies.push_back(perVertex->index);
		return perVertex;
	}
	else
	{
		Vertex* anotherVertex = perVertex->dup;
		if (anotherVertex != NULL)
			return dealWithAlreadyProcessedVertex(anotherVertex, v, t, n, indecies, vertices);
		else
		{
			Vertex* dupVertex = new Vertex((unsigned int)vertices.size(), perVertex->position);
			dupVertex->textureIndex = t - 1;
			dupVertex->normalIndex = n - 1;
			perVertex->dup = dupVertex;
			vertices.push_back(dupVertex);
			indecies.push_back(dupVertex->index);
			return dupVertex;
		}
	}
}
inline Vertex* processVertex(int v, int t, int n, vector<Vertex*>& vertices, vector<unsigned int>& indecies)
{
	Vertex* currentVertex = vertices[v - 1];
	if (!currentVertex->isSet())
	{
		currentVertex->textureIndex = t - 1;
		currentVertex->normalIndex = n - 1;
		indecies.push_back(v - 1);
		return currentVertex;
	}
	else
	{
		if (currentVertex != NULL)
			return dealWithAlreadyProcessedVertex(currentVertex, v, t, n, indecies, vertices);
	}
}
/* Convert File to OBJFile (only temp) */
FileType::OBJFile FileType::OBJFile::load(File& file, bool useTangents)
{	
	Logger::setSpace("OBJLoader");
	// Some vectors of data
	vector<Vertex*> vertices;
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

		//Vertices
		if (type == "v")
		{
			float x, y, z; iss >> x >> y >> z;
			vertices.push_back(new Vertex((unsigned int)vertices.size(), glm::vec3(x, y, z)));
		}
		//Texture Coordinates
		else if (type == "vt")
		{
			float x, y; iss >> x >> y;
			textures.push_back(glm::vec2(x, y));
		}
		//Normals
		else if (type == "vn")
		{
			float x, y, z; iss >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//Faces
		else if (type == "f")
		{
			break;
		}
		else
		{
			//if (!(type == "s" || type == "o" || type == "#"))
				//throw new WrongFileTypeExcption("OBJFile");
		}
	}
	while (getline(f, line))
	{
		istringstream iss(replaceAll(line, "/", " "));
		string type; iss >> type;
		Vertex* vert[3];
		for (unsigned int i = 0; i < 3; i++)
		{
			int v, t, n; iss >> v >> t >> n;
			Vertex* currentVertex = vertices[v - 1];
			if (!currentVertex->isSet())
			{
				currentVertex->textureIndex = t - 1;
				currentVertex->normalIndex = n - 1;
				indices.push_back(v - 1);
				vert[i] = currentVertex;
			}
			else
				vert[i] = dealWithAlreadyProcessedVertex(currentVertex, v, t, n, indices, vertices);
		}

		glm::vec2 uv0 = textures[vert[0]->textureIndex];
		glm::vec2 deltaUv1 = textures[vert[1]->textureIndex] - uv0;
		glm::vec2 deltaUv2 = textures[vert[2]->textureIndex] - uv0;

		glm::vec3 tangent = (((vert[1]->position - vert[0]->position) * deltaUv2.y) - ((vert[2]->position - vert[0]->position) * deltaUv1.y)) *
			(1.0F / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
		vert[0]->tangent = tangent;
		vert[1]->tangent = tangent;
		vert[2]->tangent = tangent;
	}

	/* Convert data to arrays */
	vector<float> positionArray = vector<float>(indices.size() * 3);
	vector<float> textureArray  = vector<float>(indices.size() * 2);
	vector<float> normalArray   = vector<float>(indices.size() * 3);
	vector<float> tangentArray = vector<float>(indices.size() * 3);
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		Vertex* vertex = vertices[i];
		glm::vec3 position = vertex->position;
		glm::vec2 texture = textures[vertex->textureIndex];
		glm::vec3 normal = normals[vertex->normalIndex];
		glm::vec3 tangent = vertex->tangent;
		tangentArray[i * 3] = tangent.x;
		tangentArray[(i * 3) + 1] = tangent.y;
		tangentArray[(i * 3) + 2] = tangent.z;
		positionArray[i * 3] = position.x;
		positionArray[(i * 3) + 1] = position.y;
		positionArray[(i * 3) + 2] = position.z;
		textureArray[i * 2] = texture.x;
		textureArray[(i * 2) + 1] = -texture.y;
		normalArray[i * 3] = normal.x;
		normalArray[(i * 3) + 1] = normal.y;
		normalArray[(i * 3) + 2] = normal.z;
	}
	for (Vertex* vertex : vertices) delete vertex;

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