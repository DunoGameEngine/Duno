#include "../Graphics/Display/Display.h"

int main() {

	using namespace Duno;
	using namespace Graphics;

	Display newDisplay;
	newDisplay.createDisplay("swag");

	while (newDisplay.running) {

		newDisplay.updateDisplay();

	}
	newDisplay.closeDisplay();

	return 0;
}