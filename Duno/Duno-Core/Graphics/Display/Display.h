#pragma once

using namespace Duno;

namespace Duno {namespace Graphics {

		class Display {

		private:
			//const long m_ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
			//const long m_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

			const char* m_title;
			int m_width;
			int m_height;
			int m_posX;
			int m_posY;
			int m_fps;
			bool m_useVsync;

			//GLFWwindow* window = NULL;

		public:
			bool running = true;

			Display();
			~Display();

			void createDisplay(char* title = "Duno_Engine", int width = 720, int height = 640,
				int fps = 60, bool useVsync = false);
			void updateDisplay();
			void closeDisplay();

		};
	}}