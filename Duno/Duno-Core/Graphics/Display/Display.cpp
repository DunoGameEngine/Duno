#include "Display.h"

Duno::Graphics::Display::Display()
{
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
	m_title = title;
	m_width = width;
	m_height = height;
	m_fps = fps;
	m_useVsync = useVsync;

	if (!glfwInit()) {
		std::cout << "idiot" << std::endl;
		running = false;
	}

	window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		running = false;
	}

	glfwMakeContextCurrent(window);
	glClearColor(0.25, 0, 0.5, 0);

}
}

void Duno::Graphics::Display::updateDisplay()
{
}

void Duno::Graphics::Display::closeDisplay()
{
}
