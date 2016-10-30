#include "../DunoGame.h"
#include "../GameUtil/Logger.h"
#include "../Assets/FileLoader/OBJFile.h"
#include "../GameUtil/Exceptions.h"
#include "../Input/DunoMouse.h"
#include "../Graphics/renderEngine/GLSkyBoxRenderer.h"
#include "../Graphics/renderEngine/GLEntityReflectiveRenderer.h"
#include "../Graphics/renderEngine/Types/Material/GLBasicMateralTypes.h"
#include <Windows.h>
using namespace Duno;
using namespace Graphics;
using namespace RenderEngine;

/* The API bit has not been done, so don't see this as the final look of the code by any means */
int main() {
	Display newDisplay;
	FileSystem::setHome("../Assets/");
	Logger::init();
	Logger::setSpace("Loader");
	Logger::logln("Started Loading");

	GLDunoGame* game = new GLDunoGame();
	game->addRenderer(new GLEntityRenderer());
	Logger::logln("Loaded Renderers");
	game->updateProjectionMatrix();
	Logger::logln("Loaded Skybox");

	GLTexture* white = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/white.png")));

	GLTexture* defuse = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/Concrete11/Concrete11.png")));
	GLTexture* bump = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/Concrete11/Concrete11_norm.png")));
	GLTexture* spec = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/Concrete11/Concrete11_spec.png")));

	GLTexture* woodTexture = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/wood/wood.png")));
	GLTexture* woodNorm = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/wood/wood_norm.png")));
	GLTexture* woodSpec = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/wood/wood_spec.png")));

	GLTexture* rockTexture = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/rocks/rocks.png")));
	GLTexture* rockNorm = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/rocks/rocks_norm.png")));

	GLTexture* brickTexture = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick/brick.png")));
	GLTexture* brickNorm = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick/brick_norm.png")));
	GLTexture* brickSpec = game->getTextureLoader()->loadTexture(FileType::ImageFile::load(FileSystem::getFile("Textures/brick/brick_spec.png")));

	GLMaterial* floor = new GLMaterialFull(defuse, bump, spec, 0.0f, 1.0f);
	GLMaterial* wood = new GLMaterialFull(woodTexture, woodNorm, woodSpec, 0.0f, 1.0f);
	GLMaterial* rocks = new GLMaterialBumped(rockTexture, rockNorm, 0.0f, 0.0f);
	GLMaterial* brick = new GLMaterialFull(brickTexture, brickNorm, brickSpec, 0.0f, 1.0f);
	GLMaterial* source = new GLMaterialBasic(white, 1.0f, 0.0f);

	PlainModel* sourceModel = game->getLoader()->load(FileType::OBJFile::load(FileSystem::getFile("Models/MatTest/source.obj")));
	PlainModel* floorModel = game->getLoader()->loadQuad(50.0f, 0.2f);

	game->getRenderer(0)->addModel(new DunoGameObject(sourceModel, source, glm::vec3(10, 1.5f, 10), glm::vec3(), glm::vec3(1, 1, 1)));
	game->getRenderer(0)->addModel(new DunoGameObject(floorModel, floor, glm::vec3(-50, 0, -50), glm::vec3(), glm::vec3(1, 1, 1)));
	
	game->getRenderer(0)->addModel(new DunoGameObject(sourceModel, source, glm::vec3(-10, 1.5f, 10), glm::vec3(), glm::vec3(1, 1, 1)));
	game->getRenderer(0)->addModel(new DunoGameObject(floorModel, wood, glm::vec3(50, 0, -50), glm::vec3(), glm::vec3(1, 1, 1)));
	
	game->getRenderer(0)->addModel(new DunoGameObject(sourceModel, source, glm::vec3(10, 1.5f, -10), glm::vec3(), glm::vec3(1, 1, 1)));
	game->getRenderer(0)->addModel(new DunoGameObject(floorModel, rocks, glm::vec3(50, 0, 50), glm::vec3(), glm::vec3(1, 1, 1)));

	game->getRenderer(0)->addModel(new DunoGameObject(sourceModel, source, glm::vec3(-10, 1.5f, -10), glm::vec3(), glm::vec3(1, 1, 1)));
	game->getRenderer(0)->addModel(new DunoGameObject(floorModel, brick, glm::vec3(-50, 0, 50), glm::vec3(), glm::vec3(1, 1, 1)));

	Logger::logln("Loaded Models");
	
	game->addLight(new PointLight(glm::vec3(10, 1.5f, 10), glm::vec3(1.0f, 1.0f, 1.0f)));
	game->addLight(new PointLight(glm::vec3(-10, 1.5f, 10), glm::vec3(1.0f, 1.0f, 1.0f)));
	game->addLight(new PointLight(glm::vec3(10, 1.5f, -10), glm::vec3(1.0f, 1.0f, 1.0f)));
	game->addLight(new PointLight(glm::vec3(-10, 1.5f, -10), glm::vec3(1.0f, 1.0f, 1.0f)));

	glClearColor(0, 0, 0, 0);
	glfwSwapInterval(0);
	try { game->startMainGameLoop(); }
	catch (DunoException* e) { MessageBoxA(0, e->errorOut().c_str(), "Duno Error", ALERT_SYSTEM_ERROR); }
	catch (...) { MessageBoxA(0, "Unknown error occurred", "Duno Error", ALERT_SYSTEM_ERROR); }

	delete game;
	delete defuse;
	delete white;
	delete bump;

	delete woodTexture;
	delete woodNorm;
	delete woodSpec;

	delete rockTexture;
	delete rockNorm;

	delete brickTexture;
	delete brickNorm;
	delete brickSpec;
	newDisplay.closeDisplay();
	return 0;
}