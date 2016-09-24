#include "../Graphics/renderEngine/GLLoader.h"
#include "../Graphics/renderEngine/GLTextureLoader.h"
#include "../Graphics/renderEngine/GLEntityRenderer.h"
#include "../Graphics/Display/Display.h"
#include "../GameUtil/Logger.h"
#include "../Assets/AssetManeger.h"
#include "../Graphics/renderEngine/Types/PlainModel.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../GameUtil/Exceptions.h"
#include "../Graphics/Display/DunoMouse.h"
#include <Windows.h>
using namespace Duno;
using namespace Graphics;
using namespace RenderEngine;

void game(Display newDisplay)
{
	Logger::init();
	Logger::setSpace("GameLoader");
	FileSystem::setHome("../Assets/");
	
	Logger::logln("Loading Display");
	newDisplay.createDisplay("swag");

	Logger::logln("Loading Assets");
	DunoCamera* cam = new DunoCamera(glm::vec3(0,-4,0), glm::vec3(), glm::vec3(1,1,1));

	GLEntityRenderer* renderer = new GLEntityRenderer();
	GLLoader* loader = new GLLoader();
	GLTextureLoader* textureLoader = new GLTextureLoader();
	/* A test scene - only as a test */
	GLTexture* defuse = textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick.png")));
	GLTexture* bump = textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick_bump.png")));
	GLMateral* mat = new GLMateral(defuse, bump);
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/testModel.obj"))), mat, glm::vec3(), glm::vec3(), glm::vec3(1,1,1)));
	/*
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/2.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/3.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/4.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/5.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/6.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/4.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/7.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/8.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/9.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/10.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/5.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/11.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/6.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/12.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/13.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/14.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/15.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/7.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/16.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/17.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/18.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/19.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/20.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/21.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/2.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/22.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/23.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	renderer->addModel(new DunoGameObject(loader->load(FileType::OBJFile::load(FileSystem::getFile("Models/test/24.obj"))), textureLoader->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/test/3.png"))), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	*/

	Logger::logln("Starting Main Game Loop");
	Logger::setSpace("GameLoop");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (newDisplay.running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam->updateMouseLook(0.2F,0.2F);
		cam->updateFreeMove(0.2F);
		renderer->render(cam);
		newDisplay.updateDisplay();
		//DunoMouse::update(glm::vec2(0, 0));
	}
	Logger::back();
	Logger::logln("Game Closing");

	delete renderer;
	delete loader;
	delete textureLoader;
}

//comment
int main() {
	Display newDisplay;

	try { game(newDisplay); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unkown error occured", "Duno Error", ALERT_SYSTEM_ERROR); }

	newDisplay.closeDisplay();
	return 0;
}