#pragma once
#include <stdio.h>
#include <list>
#include "Types\PlainModel.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../OpenGL/GL.h"
namespace Duno{namespace Graphics{namespace RenderEngine{

	class GLLoader {

	private:

		//store VBOs and VAOs for memory management
		//the list will be deleted at the end
		std::list<GLuint> vbos;
		std::list<GLuint> vaos;

		//store the number of VBOs inside VAO
		int vaoLength;

		//VAO management (vao's are required in teh new OpenGL)
		int createVAO();
		void unbindVAO();

		//VBO management + store in VAO
		GLuint storeDataInVBO(vector<float> data, unsigned int dataSize, unsigned int index);

		//bind Indices and include them ni the VAO
		void bindIndicesBuffer(vector<unsigned int> indices);

		//Delete all the VBOs and VAOs
		void cleanUp();
	public:

		//constructor and destructor of the class constructor
		GLLoader();
		~GLLoader();

		//load data into the model, return new model
		Types::PlainModel* load(vector<float> positions, vector<float> textures, vector<float> normals, vector<unsigned int> indices);
		Types::PlainModel* loadSkybox();

		Types::PlainModel* load(FileType::OBJFile file);

	};


} } }