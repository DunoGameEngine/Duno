#include "GLShadowRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

#define MVP_MATRIX 0

GLShadowRenderer::GLShadowRenderer()
{
	GLShader* shader = new GLShader("shadow");
	shader->addAtribute("position");
	shader->addAtribute("textureCoords");
	shader->addAtribute("normal");
	shader->compile();
	
	shader->allocateLocations(1);
	shader->setLocation(MVP_MATRIX, "mvp");
	setShader(shader);

	float size = 20;
	shadow_projectionMatix = glm::ortho(-size, size, size, -size);//glm::perspective(70.0F, 1280.0F / 720.0F, 0.1F, 1000.0F);
	shadow_cam = new DunoCamera(glm::vec3(), glm::vec3(90, 0, 0), glm::vec3(1, 1, 1));
}

void GLShadowRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	shadow_cam->setPosition(glm::vec3(cam->getPosition().x, 0, cam->getPosition().z));// + glm::vec3(0, -20, 0));
	shadow_cam->setRoation(glm::vec3(90, 0, 0));
	getShader()->loadMatrix(getShadowMatrix(), MVP_MATRIX);
}