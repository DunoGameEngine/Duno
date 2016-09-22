#include "../Graphics/renderEngine/GLLoader.h"
#include "../Graphics/renderEngine/GLTextureLoader.h"
#include "../Graphics/renderEngine/GLEntityRenderer.h"
#include "../Graphics/Display/Display.h"
#include "../GameUtil/Logger.h"
#include "../Assets/AssetManeger.h"
#include "../Graphics/renderEngine/Types/PlainModel.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../GameUtil/Exceptions.h"
#include <Windows.h>
using namespace Duno;
using namespace Graphics;
using namespace RenderEngine;

void game(Display newDisplay)
{
	Logger::init();
	Logger::setSpace("GameLoader");
	FileSystem::setHome("../Assets/");

	Logger::logln("Loading Assets");
	AssetManeger<FileType::OBJFile, string> modelManeger;
	//modelManeger.loadAsset(FileType::OBJFile::load(FileSystem::getFile("models/test.obj")), "Test Model");
	//modelManeger.loadAsset(FileType::OBJFile::load(FileSystem::getFile("models/testModel.obj")), "Test Scene");
	
	Logger::logln("Loading Display");
	newDisplay.createDisplay("swag");

	GLEntityRenderer* renderer = new GLEntityRenderer();
	GLLoader* loader = new GLLoader();
	GLTextureLoader* textureLoader = new GLTextureLoader();
	GLTexture* testTexture = textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/uv.png")));
	renderer->addModel(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/testModel.obj"))));

	Logger::logln("Starting Main Game Loop");
	Logger::setSpace("GameLoop");
	glEnable(GL_DEPTH_TEST);
	while (newDisplay.running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		testTexture->bind();
		renderer->render();
		newDisplay.updateDisplay();
	}
	Logger::back();
	Logger::logln("Game Closing");

	delete renderer;
	delete loader;
	delete textureLoader;
	delete testTexture;
}

int main() {
	Display newDisplay;

	try { game(newDisplay); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unkown error occured", "Duno Error", ALERT_SYSTEM_ERROR); }

	newDisplay.closeDisplay();
	return 0;
}