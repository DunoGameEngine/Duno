#include "GLEntityRenderer.h"
#include "../GameUtil/GameTimer.h"
#include <glm\gtc\matrix_transform.hpp>

#define MVP_MATRIX 0
#define LIGHT_POS 1

GLEntityRenderer::GLEntityRenderer()
{
	GLShader* shader = new GLShader("entity");
	shader->addAtribute("position");
	shader->addAtribute("texture");
	shader->addAtribute("normal");
	shader->compile();

	shader->allocateLocations(2);
	shader->setLocation(MVP_MATRIX, "mvp");
	shader->setLocation(LIGHT_POS, "lightPos");
	setShader(shader);

	//projectionMatrix = glm::perspective(70.0F, 1280.0F/720.0F, 0.1F, 1000.0F);
}

void GLEntityRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	getShader()->loadMatrix(projectionMatrix * cam->getTransformationMatrix(), MVP_MATRIX);
	getShader()->loadVector(glm::vec3(sin(test)*10.0F, 7, 0), LIGHT_POS);
	//getShader()->loadVector(-cam->getPosition(), LIGHT_POS);
	test += GameTimer::getFrameTimeSeconds() * 1.0F;
}