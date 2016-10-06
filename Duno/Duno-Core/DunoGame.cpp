#include "DunoGame.h"
#include "GameUtil/GameTimer.h"
#include "Graphics\Display\DunoMouse.h"
#include "Graphics\Display\DunoDisplayInfo.h"

DunoGame::DunoGame(const char* name)
{
	display = new Display();
	display->createDisplay(name);
	mainCamera = new DunoCamera(glm::vec3(), glm::vec3(), glm::vec3(1, 1, 1));
}
void DunoGame::startMainGameLoop()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (display->running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		onRender();
		display->updateDisplay();
		GameTimer::update();
	}
}
DunoGame::~DunoGame()
{
	onCleanUp();
	delete display;
}

GLDunoGame::GLDunoGame() : DunoGame("GLDunoWindow")
{
	renderer = new GLMainRenderer(mainCamera);
	loader = new GLLoader();
	textureLoader = new GLTextureLoader();
}
void GLDunoGame::onRender()
{
	DunoMouse::setDisabled(DunoMouse::isLeftMouseDown());
	mainCamera->updateMouseLook(0.2F, 0.2F, DunoMouse::isLeftMouseDown());
	mainCamera->updateFreeMove(10.0F);
	renderer->renderScene();

	if (DunoDisplayInfo::hasResized())
	{
		renderer->updateProjectionMatrix();
		glViewport(0, 0, DunoDisplayInfo::getWidth(), DunoDisplayInfo::getHeight());
	}
}
void GLDunoGame::onCleanUp()
{
	delete renderer;
	delete loader;
	delete textureLoader;
}