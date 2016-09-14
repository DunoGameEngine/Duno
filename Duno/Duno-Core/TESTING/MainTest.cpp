#include "../Graphics/Display/Display.h"
#include "../GameUtil/Logger.h"

int main() {

	Logger::init();
	Logger::setSpace("GameLoader");

	using namespace Duno;
	using namespace Graphics;

	Logger::logln("Loading Display");
	Display newDisplay;
	newDisplay.createDisplay("swag");

	Logger::logln("Starting Main Game Loop");
	Logger::setSpace("GameLoop");
	while (newDisplay.running) {

		newDisplay.updateDisplay();

	}
	Logger::back();
	Logger::logln("Game Closing");
	newDisplay.closeDisplay();

	return 0;
}