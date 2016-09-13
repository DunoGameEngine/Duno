#include "Display.h"

Duno::Graphics::Display::Display()
{
	m_title = "Duno_Engine";
	m_width = 720;
	m_height = 640;
	//m_posX = (m_ScreenWidth / 2) - (m_width / 2);
	//m_posY = (m_ScreenHeight / 2) - (m_height / 2);
	m_fps = 60;
	m_useVsync = false;
}

Duno::Graphics::Display::~Display()
{
}

void Duno::Graphics::Display::createDisplay(char * title, int width, int height, int fps, bool useVsync)
{
}

void Duno::Graphics::Display::updateDisplay()
{
}

void Duno::Graphics::Display::closeDisplay()
{
}
