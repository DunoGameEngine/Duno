#pragma once
#include <stdio.h>
#include <list>
#include <vector>
#include "Types\PlainModel.h"
#include "../OpenGL/GL.h"
namespace Duno{namespace Graphics{namespace RenderEngine{

	class Loader {

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
		GLuint storeDataInVBO(int dataSize, float data[]);

		//bind Indices and include them ni the VAO
		void bindIndicesBuffer(int indices[]);

		//Delete all the VBOs and VAOs
		void cleanUp();
	public:

		//constructor and destructor of the class constructor
		Loader();
		~Loader();

		//load data into the model, return new model
		Types::PlainModel load(float data[], int indices[]);



	};


} } }