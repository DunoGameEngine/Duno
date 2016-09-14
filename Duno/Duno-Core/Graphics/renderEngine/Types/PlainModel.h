#pragma once

namespace Duno{namespace Graphics{ namespace RenderEngine{

	class PlainModel {

	private:
		int vaoID;
		int vaoLength;
		int vertexNumber;
		bool hasIndexBuffer;
	public:

		//a plain vertex model has to contain
		//ID of it's vao, number of vertices
		//length of the vao and whever it uses indices buffer
		PlainModel(int vaoID, int vertex, int vaoLength, bool index);

		//get an ID of model's VAO
		int getVaoID();

		//get the size of the VAO
		int getVaoLength();

		//set the size of the VAO
		//used in the renderer
		void setVaoLength(int length);

		//get the number of vertices
		int getVertexNumber();

		//if the model has an indices buffer
		bool getHasIndexBuffer();

	};

} } }