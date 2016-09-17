#include "../Graphics/Display/Display.h"
#include "../GameUtil/Logger.h"
#include "../Assets/AssetManeger.h"
#include "../Graphics/renderEngine/Types/PlainModel.h"

int main() {
	
	Logger::init();
	Logger::setSpace("GameLoader");
	
	Logger::logln("Loading Assets");
	AssetManeger<Duno::Graphics::RenderEngine::Types::PlainModel> modelManeger;
	modelManeger.loadAsset(new Duno::Graphics::RenderEngine::Types::PlainModel(0, 0, 0, false));

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