#include "../DunoGame.h"
#include "../GameUtil/Logger.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../GameUtil/Exceptions.h"
#include "../Graphics/Display/DunoMouse.h"
#include "../Graphics/renderEngine/GLSkyBoxRenderer.h"
#include "../Graphics/renderEngine/GLEntityReflectiveRenderer.h"
#include <Windows.h>
using namespace Duno;
using namespace Graphics;
using namespace RenderEngine;

int main() {
	Display newDisplay;
	FileSystem::setHome("../Assets/");
	Logger::init();
	Logger::setSpace("Loader");
	Logger::logln("Started Loading");

	GLDunoGame* game = new GLDunoGame();
	GLTexture* skybox = game->getTextureLoader()->loadCubeMap(FileSystem::getFile("Textures/Skybox/city/"));
	game->addRenderer(new GLEntityRenderer());
	game->addRenderer(new GLEntityReflectiveRenderer(skybox));
	game->addRenderer(new GLSkyBoxRenderer(game->getLoader()));
	Logger::logln("Loaded Renderers");
	game->updateProjectionMatrix();
	game->getRenderer(2)->addModel(new DunoGameObject(game->getLoader()->loadSkybox(), new GLMateral(skybox), glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	Logger::logln("Loaded Skybox");

	GLTexture* defuse = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick.png")));
	GLTexture* bump = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick_norm.png")));
	GLMateral* mat = new GLMateral(defuse, bump);
	game->getRenderer(0)->addModel(new DunoGameObject(game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/testModel.obj"))), mat, glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	//game->getRenderer(1)->addModel(new DunoGameObject(game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/bunny.obj"))), mat, glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));
	//game->getRenderer(1)->addModel(new DunoGameObject(game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/dragon.obj"))), mat, glm::vec3(20, 0, 0), glm::vec3(), glm::vec3(1, 1, 1)));
	//game->getRenderer(1)->addModel(new DunoGameObject(game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/test.obj"))), mat, glm::vec3(-20, 0, 0), glm::vec3(), glm::vec3(1, 1, 1)));
	Logger::logln("Loaded Models");

	glfwSwapInterval(0);
	try { game->startMainGameLoop(); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unkown error occured", "Duno Error", ALERT_SYSTEM_ERROR); }

	delete game;
	newDisplay.closeDisplay();
	return 0;
}