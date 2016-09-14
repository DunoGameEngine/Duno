#pragma once

namespace Duno{namespace Graphics{ namespace RenderEngine{

	class PlainModel {

	private:

	public:

		//a plain vertex model has to contain
		//ID of it's vao, number of vertices
		//length of the vao and whever it uses indices buffer
		PlainModel(int vaoID, int vertex, int vaoLength, bool index);


	};

} } }