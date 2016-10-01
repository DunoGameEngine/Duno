#pragma once
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

namespace Duno2{namespace Graphics{


	class Display {
	private:
		GLFWwindow* m_window;



	public:

		void createDisplay(int width, int height,const char* title);
		void updateDisplay();
		void closeDisplay();
	};
} }

