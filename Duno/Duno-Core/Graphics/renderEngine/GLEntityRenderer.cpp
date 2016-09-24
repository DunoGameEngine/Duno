#include "GLEntityRenderer.h"
#include "../GameUtil/GameTimer.h"
#include <glm\gtc\matrix_transform.hpp>

#define MVP_MATRIX 0
#define POINT_LIGHTPOS 1
#define POINT_LIGHTCOLOUR 2
#define POINT_LENGTH 3
#define DIR_LIGHTDIR 4
#define DIR_LENGTH 5

GLEntityRenderer::GLEntityRenderer()
{
	GLShader* shader = new GLShader("entity");
	shader->addAtribute("position");
	shader->addAtribute("texture");
	shader->addAtribute("normal");
	shader->compile();

	shader->allocateLocations(5);
	shader->setLocation(MVP_MATRIX, "mvp");
	shader->setLocation(POINT_LIGHTPOS, "point_lightPos");
	shader->setLocation(POINT_LIGHTCOLOUR, "point_lightColour");
	shader->setLocation(POINT_LENGTH, "point_length");
	shader->setLocation(DIR_LIGHTDIR, "dir_lightDir");
	shader->setLocation(DIR_LENGTH, "dir_length");
	setShader(shader);

	//projectionMatrix = glm::perspective(70.0F, 1280.0F/720.0F, 0.1F, 1000.0F);
}

void GLEntityRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	getShader()->loadMatrix(projectionMatrix * cam->getTransformationMatrix(), MVP_MATRIX);
	getShader()->loadVectorArray(new glm::vec3[2]{ glm::vec3(sin(test)*10.0F, (sin(test*2)*5)+7, 0), glm::vec3(-sin(test)*10.0F, (sin(-test*2) * 5) + 7, 0) }, 2, POINT_LIGHTPOS);
	getShader()->loadVectorArray(new glm::vec3[2]{ glm::vec3(0,1,0), glm::vec3(0,0,1) }, 2, POINT_LIGHTCOLOUR);
	getShader()->loadInt(2, POINT_LENGTH);
	getShader()->loadInt(0, DIR_LENGTH);
	test += GameTimer::getFrameTimeSeconds() * 1.0F;
}
