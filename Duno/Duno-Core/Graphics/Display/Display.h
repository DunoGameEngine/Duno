#pragma once
#include <stdio.h>      /* printf */
#include <stdlib.h>
#include "../OpenGL/GL.h"
#include <GLFW\glfw3.h>
#pragma comment(lib, "opengl32.lib")


namespace Duno {namespace Graphics {

		class Display {

		private:
			//const long m_ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
			//const long m_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

			//decribe properties of the window
			const char* m_title;
			int m_width;
			int m_height;
			int m_fps;
			bool m_useVsync;	

			//create a new glfw window and assing it to null
			GLFWwindow* window = NULL;

		public:

			//can use this to check if the game loop should be running
			bool running = true;

			//just initialize constructor and destructor
			Display();
			~Display();

			//create the display method
			void createDisplay(char* title = "Duno_Engine", int width = 720, int height = 640,
				int fps = 60, bool useVsync = false);

			//will be called each frame
			void updateDisplay();

			//once it's time to close the window
			void closeDisplay();

		};
}}