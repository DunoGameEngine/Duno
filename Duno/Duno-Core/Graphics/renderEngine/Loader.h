#pragma once
#include <stdio.h>
#include <list>
#include <vector>
namespace Duno{namespace Graphics{namespace RenderEngine{

	class Loader {

	private:

		//store VBOs and VAOs for memory management
		//the list will be deleted at the end
		std::list<int> vbos;
		std::list<int> vaos;

		//store the number of VBOs inside VAO
		int vaoLength;

	public:

		//constructor and destructor of the class constructor
		Loader();
		~Loader();

		void load();


	};


} } }