#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

namespace Duno2{namespace Graphics{


	class Display {
		
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		const char* m_title;


	public:
		//Declare true if the window should close
		bool shouldClose = false;

		//Create a new display and assign it to m_window
		void createDisplay(int width = 600, int height = 400,
			const char* title = "Duno Game Engine");

		//Poll the events, swap buffers
		void updateDisplay();

		//Terminate GLFW
		void closeDisplay();

		//Get width of the window
		int getDisplayWidth() { return m_width; }

		//Get height of the window
		int getDisplayHeight() { return m_height; }

		//Get title of the window
		const char* getDisplayTitle() { return m_title; }
	};
} }

