#include "Display.h"

Duno::Graphics::Display::Display()
{

	//set default properties for a window
	m_title = "Duno_Engine";
	m_width = 720;
	m_height = 640;
	m_fps = 60;
	m_useVsync = false;
}

Duno::Graphics::Display::~Display()
{
}

void Duno::Graphics::Display::createDisplay(char * title, int width, int height, int fps, bool useVsync)
{
	//set the private members to the value of passed in parameters
	m_title			= title;
	m_width			= width;
	m_height		= height;
	m_fps			= fps;
	m_useVsync		= useVsync;

	//initialize glfw
	if (!glfwInit()) {
		printf("glfw could not be initialized");
		running = false;
	}

	//create in glfw window, if it didn't happen then erminate glfw
	window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		running = false;
	}

	//enable usage of opengl in the window, set the clear colour
	glfwMakeContextCurrent(window);

	//set the clear colour
	glClearColor(0.25, 0, 0.5, 0);

}


void Duno::Graphics::Display::updateDisplay()
{
	//check if should continue running 
	if (glfwWindowShouldClose(window)) {
		running = false;
	}

	//delete if renderer does that
	glClear(GL_COLOR_BUFFER_BIT); 

	//swap images
	glfwSwapBuffers(window);	

	//get the input
	glfwPollEvents();		

}

void Duno::Graphics::Display::closeDisplay()
{

	//destroy glwf window
	glfwDestroyWindow(window);

	//terminate glfw
	glfwTerminate();
}
