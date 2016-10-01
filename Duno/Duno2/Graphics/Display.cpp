#include "Display.h"

using namespace Duno2;
using namespace Graphics;

void Display::createDisplay(int width, int height,const char* title) {

	//Initialize GLFW library
	if (!glfwInit())
		std::cout << "Could not initialize GLFW" << std::endl;
	else
		std::cout << "GLFW initialized properly" << std::endl;

	//Create new GLFW window
	m_window = glfwCreateWindow(width, height, title, NULL, NULL);

	//Check if window was created correctly
	if (!m_window)
	{
		glfwTerminate();
		std::cout << "GLFW window was not created correctly" << std::endl;
		
	}

}


void Display::updateDisplay() {

	//Poll events
	glfwPollEvents();

	//Swap buffers
	glfwSwapBuffers(m_window);

}

void Display::closeDisplay() {

	glfwTerminate();

}