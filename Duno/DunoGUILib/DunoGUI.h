#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

namespace DunoGUI
{
	/* Static Insistence Of WinAPI */
	class DunoGUIInsistence
	{
	public:
		/* Initialize Insistence */
		static void init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

		/* Getters */
		static HINSTANCE getInstence() { return m_instance; }
		static int getCMDShow()        { return m_cmd_show; }

		/* Start Main Loop Running */
		static int startLoop();
	private:
		/* Store Insistence Data */
		static HINSTANCE m_instance; 
		static HINSTANCE m_prev_instance;
		static LPSTR m_lp_cmd_line;
		static int m_cmd_show;
	};
}