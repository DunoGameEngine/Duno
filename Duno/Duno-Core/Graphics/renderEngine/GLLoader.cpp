#include "GLLoader.h"
using namespace Duno::Graphics::RenderEngine;

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
	return new Types::PlainModel(VAO, 0, indices.size(), true);
}

Types::PlainModel* GLLoader::load(FileType::OBJFile file)
{
	ModelInfo* info = file.getInfo();
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


GLuint GLLoader::storeDataInVBO(vector<float> data, unsigned int dataSize, unsigned int index)
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
	glVertexAttribPointer(index, dataSize, GL_FLOAT, GL_FALSE, 0, 0);

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

