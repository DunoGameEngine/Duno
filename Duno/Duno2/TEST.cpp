#include <iostream>
#include "Graphics\Display.h"

using namespace Duno2;
using namespace Graphics;

int main() {
	
	Display window = Display();
	
	window.createDisplay();

	while (!window.shouldClose) {

		window.updateDisplay();

	}

	window.closeDisplay();

	return 0;
}