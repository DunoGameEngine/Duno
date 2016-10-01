#include "Display.h"

using namespace Duno2;
using namespace Graphics;

void Display::createDisplay() {

	//Initialize GLFW library
	if (!glfwInit())
		std::cout << "Could not initialize GLFW" << std::endl;
	else
		std::cout << "GLFW initialized properly" << std::endl;

}

void Display::updateDisplay() {


}

void Display::closeDisplay() {



}