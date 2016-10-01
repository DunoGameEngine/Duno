#include "Display.h"



void Duno2::Graphics::Display::createDisplay(int width, int height,const char* title) {


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


void Duno2::Graphics::Display::updateDisplay() {

	if (glfwWindowShouldClose(m_window))
		shouldClose = true;

	//Poll events
	glfwPollEvents();

	//Swap buffers
	glfwSwapBuffers(m_window);

}

void Duno2::Graphics::Display::closeDisplay() {

	glfwTerminate();

}