#include "DunoGUI.h"
#include "DunoWindow.h"
#include <stdio.h>
#include <tchar.h>

#include "DunoLabel.h"
#include "DunoButton.h"
using namespace DunoGUI;

/* Create Console For Debug */
FILE *g_ic_file_cout_stream; FILE *g_ic_file_cin_stream;
bool InitConsole()
{
	if (!AllocConsole()) { return false; }
	if (freopen_s(&g_ic_file_cout_stream, "CONOUT$", "w", stdout) != 0) { return false; } // For std::cout 
	if (freopen_s(&g_ic_file_cin_stream, "CONIN$", "w+", stdin) != 0) { return false; } // For std::cin
	return true;
}

/* Window's main function, the program will start here */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//InitConsole();

	/* Initialize the insistence */
	DunoGUIInsistence::init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	
	/* Create a new window */
	DunoWindow* window = new DunoWindow(800, 600);
	
	/* Define the layout and add widgets */
	DunoLayout* layout = new DunoLayout(DUNOLAYOUT_HORZ, 10);
	window->addWidget(new DunoButton(layout, "Test Button", 120, 60));
	window->addWidget(new DunoButton(layout, "Test Button", 120, 60));
	window->addWidget(new DunoButton(layout, "Test Button", 120, 60));
	window->addWidget(new DunoButton(layout, "Test Button", 120, 60));

	layout->nextLine();
	DunoButton* button = new DunoButton(layout, "Click Me", 510, 60);
	button->setOnClick([] { MessageBox(NULL, _T("You Clicked A Button"), _T("Click Me Button"), NULL); });
	window->addWidget(button);

	layout->nextLine();
	window->addWidget(new DunoButton(layout, "Test Button", 250, 60));
	window->addWidget(new DunoButton(layout, "Test Button", 250, 60));

	/* Create the window */
	window->initWindow();

	/* Run the WinAPI loop */
	int out = DunoGUIInsistence::startLoop();
	
	/* Clean up */
	delete window;
	delete layout;
	return out;
}