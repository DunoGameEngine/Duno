//#include "..\..\..\Duno2\Graphics\Display.h" - Don't include from an outside project
#include "Display.h"
#include "../Input/DunoMouse.h"
#include "../Input/DunoKeyboard.h"
#include "Display/DunoDisplayInfo.h"

Duno::Graphics::Display::Display()
{

	//set default properties for a window
	m_title = "Duno_Engine";
	m_width = 1280;
	m_height = 720;
	m_fps = 60;
	m_useVsync = false;
}

Duno::Graphics::Display::~Display()
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	DunoMouse::update(glm::vec2(xpos, ypos));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (action == GLFW_PRESS)
		DunoKeyboard::addKey(key);
	if (action == GLFW_RELEASE)
		DunoKeyboard::removeKey(key);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		DunoMouse::setClick(action == GLFW_PRESS, 0);
	else if (button == GLFW_MOUSE_BUTTON_LEFT)
		DunoMouse::setClick(action == GLFW_PRESS, 1);
	else if (button == GLFW_MOUSE_BUTTON_LEFT)
		DunoMouse::setClick(action == GLFW_PRESS, 2);
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
	DunoDisplayInfo::setSize(width, height);
}
void Duno::Graphics::Display::createDisplay(const char * title, int width, int height, int fps, bool useVsync)
{
	//set the private members to the value of passed in parameters
	m_title			= title;
	m_width			= width;
	m_height		= height;
	m_fps			= fps;
	m_useVsync		= useVsync;
	DunoDisplayInfo::setSize(width, height);

	//initialize glfw
	if (!glfwInit()) {
		printf("glfw could not be initialized");
		running = false;
	}

	//create in glfw window, if it didn't happen then terminate glfw
	window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		running = false;
	}
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//enable usage of opengl in the window, set the clear colour
	glfwMakeContextCurrent(window);

	//set the clear colour
	glClearColor(0.25, 0, 0.5, 0);

	glewInit();

}


void Duno::Graphics::Display::updateDisplay()
{
	//check if should continue running 
	if (glfwWindowShouldClose(window)) {
		running = false;
	}

	if (DunoMouse::isDisabled())
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
