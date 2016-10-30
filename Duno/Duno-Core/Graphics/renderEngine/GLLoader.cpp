#include "GLLoader.h"
#include <glm/glm.hpp>
using namespace Duno::Graphics::RenderEngine;

/*                                      */
/*                                      */
/*            TO BE CLEANED             */
/*                                      */
/*                                      */

GLLoader::GLLoader()
{
	vaoLength = 0;
}

GLLoader::~GLLoader()
{
	cleanUp();
}

Types::PlainModel* GLLoader::load(vector<float> positions, vector<float> textures, vector<float> normals, vector<unsigned int> indices)
{
	//create new VAO
	int VAO = createVAO();

	bindIndicesBuffer(indices);
	storeDataInVBO(positions, 3, 0);
	storeDataInVBO(textures, 2, 1);
	storeDataInVBO(normals, 3, 2);

	unbindVAO();
	return new Types::PlainModel(VAO, 0, (unsigned int)indices.size(), true);
}
Types::PlainModel* GLLoader::load(vector<float> positions, vector<float> textures, vector<float> normals, vector<unsigned int> indices, vector<float> tangents)
{
	//create new VAO
	int VAO = createVAO();

	bindIndicesBuffer(indices);
	storeDataInVBO(positions, 3, 0);
	storeDataInVBO(textures, 2, 1);
	storeDataInVBO(normals, 3, 2);
	storeDataInVBO(tangents, 3, 3);

	unbindVAO();
	return new Types::PlainModel(VAO, 0, (unsigned int)indices.size(), true);
}
Types::PlainModel* GLLoader::loadSkybox()
{
	int VAO = createVAO();
	float size = 500.0F;
	float positions[] = {
		-size,  size, -size,
		-size, -size, -size,
		size, -size, -size,
		size, -size, -size,
		size,  size, -size,
		-size,  size, -size,

		-size, -size,  size,
		-size, -size, -size,
		-size,  size, -size,
		-size,  size, -size,
		-size,  size,  size,
		-size, -size,  size,

		size, -size, -size,
		size, -size,  size,
		size,  size,  size,
		size,  size,  size,
		size,  size, -size,
		size, -size, -size,

		-size, -size,  size,
		-size,  size,  size,
		size,  size,  size,
		size,  size,  size,
		size, -size,  size,
		-size, -size,  size,

		-size,  size, -size,
		size,  size, -size,
		size,  size,  size,
		size,  size,  size,
		-size,  size,  size,
		-size,  size, -size,

		-size, -size, -size,
		-size, -size,  size,
		size, -size, -size,
		size, -size, -size,
		-size, -size, size,
		size, -size,  size
	};
	vector<float> positionsVector = vector<float>(begin(positions), end(positions));
	storeDataInVBO(positionsVector, 3, 0);
	unbindVAO();
	return new Types::PlainModel(VAO, 0, (unsigned int)positionsVector.size(), false);
}
Types::PlainModel* GLLoader::loadQuad(float size, float textureScale)
{
	int VAO = createVAO();
	float texture = size * textureScale;
	float positions[] = {
		-size, 0, -size,
		-size, 0,  size,
		size, 0, -size,
		size, 0, -size,
		-size, 0, size,
		size, 0,  size
	};
	float textures[] = {
		-texture, -texture,
		-texture, texture,
		texture, -texture,
		texture, -texture,
		-texture, texture,
		texture, texture
	};
	float normals[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};
	float tangents[18];

	{
		glm::vec2 uv0 = glm::vec2(-size, -size);
		glm::vec2 deltaUv1 = glm::vec2(-size, size) - uv0;
		glm::vec2 deltaUv2 = glm::vec2(size, -size) - uv0;
		glm::vec3 tangent = (((glm::vec3(-size, 0, size) - glm::vec3(-size, 0, -size)) * deltaUv2.y) - ((glm::vec3(size, 0, -size) - glm::vec3(-size, 0, -size)) * deltaUv1.y)) *
			(1.0F / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
		tangents[0] = tangent.x;
		tangents[1] = tangent.y;
		tangents[2] = tangent.z;

		tangents[3] = tangent.x;
		tangents[4] = tangent.y;
		tangents[5] = tangent.z;

		tangents[6] = tangent.x;
		tangents[7] = tangent.y;
		tangents[8] = tangent.z;
	}
	{
		glm::vec2 uv0 = glm::vec2(size, -size);
		glm::vec2 deltaUv1 = glm::vec2(-size, size) - uv0;
		glm::vec2 deltaUv2 = glm::vec2(size, size) - uv0;
		glm::vec3 tangent = (((glm::vec3(-size, 0, size) - glm::vec3(size, 0, -size)) * deltaUv2.y) - ((glm::vec3(size, 0, size) - glm::vec3(size, 0, -size)) * deltaUv1.y)) *
			(1.0F / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
		tangents[9] = tangent.x;
		tangents[10] = tangent.y;
		tangents[11] = tangent.z;

		tangents[12] = tangent.x;
		tangents[13] = tangent.y;
		tangents[14] = tangent.z;

		tangents[15] = tangent.x;
		tangents[16] = tangent.y;
		tangents[17] = tangent.z;
	}

	vector<float> positionsVector = vector<float>(begin(positions), end(positions));
	vector<float> texturesVector = vector<float>(begin(textures), end(textures));
	vector<float> normalsVector = vector<float>(begin(normals), end(normals));
	vector<float> tangentsVector = vector<float>(begin(tangents), end(tangents));
	storeDataInVBO(positionsVector, 3, 0);
	storeDataInVBO(texturesVector, 2, 1);
	storeDataInVBO(normalsVector, 3, 2);
	storeDataInVBO(tangentsVector, 3, 3);
	unbindVAO();
	return new Types::PlainModel(VAO, 0, (unsigned int)positionsVector.size(), false);
}

Types::PlainModel* GLLoader::load(FileType::OBJFile file)
{
	ModelInfo* info = file.getInfo();
	if (info->useTangents)
		return load(info->positions, info->textures, info->normals, info->indices, info->tangents);
	return load(info->positions, info->textures, info->normals, info->indices);
}

int GLLoader::createVAO()
{
	GLuint vaoID;

	//Generate new vao
	glGenVertexArrays(1,&vaoID);

	//add VAO to the list
	vaos.push_back(vaoID);	

	//bind the vao
	glBindVertexArray(vaoID);	

	return vaoID;
}

void GLLoader::unbindVAO()
{
	glBindVertexArray(0);
}


GLuint GLLoader::storeDataInVBO(vector<float> data, unsigned int datasize, unsigned int index)
{
	//create new gl int variable
	GLuint vboID;

	//assign it to a new buffer
	glGenBuffers(1, &vboID);

	//add vboID to vbos list
	vbos.push_back(vboID);

	//bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, datasize, GL_FLOAT, GL_FALSE, 0, 0);

	//increase the number of vbos in the vao
	vaoLength++;

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vboID;

}


void GLLoader::bindIndicesBuffer(vector<unsigned int> indices)
{

	GLuint vboID;
	glGenBuffers(1, &vboID);

	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

}

void GLLoader::cleanUp()
{
	for (GLuint vbo : vbos) {
		glDeleteBuffers(1,&vbo);																//delete vbos
	}

	for (GLuint vao : vaos) {
		glDeleteVertexArrays(1,&vao);															//delete vaos
	}
}

