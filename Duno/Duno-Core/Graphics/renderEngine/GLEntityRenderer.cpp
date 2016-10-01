#include "GLEntityRenderer.h"
#include "GLTextureLoader.h"
#include "../GameUtil/GameTimer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
using namespace std;

#define MVP_MATRIX 0
#define POINT_LIGHTPOS 1
#define POINT_LIGHTCOLOUR 2
#define POINT_LENGTH 3
#define DIR_LIGHTDIR 4
#define DIR_LENGTH 5

GLEntityRenderer::GLEntityRenderer(string shaderName, unsigned int locationExt)
{
	GLShader* shader = new GLShader(shaderName);
	shader->addAtribute("position");
	shader->addAtribute("texture");
	shader->addAtribute("normal");
	shader->addAtribute("tangent");
	shader->compile();

	shader->allocateLocations(6 + locationExt);
	shader->setLocation(MVP_MATRIX, "mvp");
	shader->setLocation(POINT_LIGHTPOS, "point_lightPos");
	shader->setLocation(POINT_LIGHTCOLOUR, "point_lightColour");
	shader->setLocation(POINT_LENGTH, "point_length");
	shader->setLocation(DIR_LIGHTDIR, "dir_lightDir");
	shader->setLocation(DIR_LENGTH, "dir_length");
	setShader(shader);
}

void GLEntityRenderer::onRenderAll(DunoCamera* cam) {}

void GLEntityRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLTextureLoader::bindTexture(model->getMateral()->getDefuse(), 0);
	GLTextureLoader::bindTexture(model->getMateral()->getBump(), 1);

	getShader()->loadMatrix(projectionMatrix * cam->getTransformationMatrix() * model->getTransformationMatrix(), MVP_MATRIX);
	glm::vec3 lightPos[1] = { glm::vec3(sin(test) * 10, 4, 0) };
	glm::vec3 lightColour[1] = { glm::vec3(1, 1, 1) };
	getShader()->loadVectorArray(lightPos, 1, POINT_LIGHTPOS);
	getShader()->loadVectorArray(lightColour, 1, POINT_LIGHTCOLOUR);
	getShader()->loadInt(1, POINT_LENGTH);
	//getShader()->loadVectorArray(new glm::vec3[1]{ glm::vec3(0.2,-1,0.2) }, 1, DIR_LIGHTDIR);
	getShader()->loadInt(0, DIR_LENGTH);
	test += GameTimer::getFrameTimeSeconds() * 1.0F;
	addRenderModel(model, cam);
}
