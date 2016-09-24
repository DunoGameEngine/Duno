#include "../DunoGame.h"
#include "../GameUtil/Logger.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../GameUtil/Exceptions.h"
#include "../Graphics/Display/DunoMouse.h"
#include <Windows.h>
using namespace Duno;
using namespace Graphics;
using namespace RenderEngine;

int main() {
	Display newDisplay;
	FileSystem::setHome("../Assets/");

	GLDunoGame* game = new GLDunoGame();
	game->addRenderer(new GLEntityRenderer());
	game->updateProjectionMatrix();

	GLTexture* defuse = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick.png")));
	GLTexture* bump = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick_bump.png")));
	GLMateral* mat = new GLMateral(defuse, bump);
	game->getRenderer(0)->addModel(new DunoGameObject(game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/testModel.obj"))), mat, glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1)));

	glfwSwapInterval(0);
	try { game->startMainGameLoop(); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unkown error occured", "Duno Error", ALERT_SYSTEM_ERROR); }

	delete game;
	newDisplay.closeDisplay();
	return 0;
}