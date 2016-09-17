#include "../Graphics/Display/Display.h"
#include "../GameUtil/Logger.h"
#include "../Assets/AssetManeger.h"
#include "../Graphics/renderEngine/Types/PlainModel.h"
#include "../Assets/FileLoader/OBJFile.h"
using namespace Duno;
using namespace Graphics;

void game(Display& newDisplay)
{
	Logger::init();
	Logger::setSpace("GameLoader");
	FileSystem::setHome("../Assets/");

	Logger::logln("Loading Assets");
	AssetManeger<OBJFile> modelManeger;
	modelManeger.loadAsset(OBJFile::load(FileSystem::getFile("models/test.obj")));

	Logger::logln("Loading Display");
	newDisplay.createDisplay("swag");

	Logger::logln("Starting Main Game Loop");
	Logger::setSpace("GameLoop");
	while (newDisplay.running) {
		newDisplay.updateDisplay();
	}
	Logger::back();
	Logger::logln("Game Closing");
}

#if defined(_WIN32)
#include <Windows.h>
#include "../GameUtil/Exceptions.h"
#endif
int main() {
	Display newDisplay;
#if defined(_WIN32)
	try { game(newDisplay); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unkown error occured", "Duno Error", ALERT_SYSTEM_ERROR); }
#else
	game();
#endif

	newDisplay.closeDisplay();
	return 0;
}