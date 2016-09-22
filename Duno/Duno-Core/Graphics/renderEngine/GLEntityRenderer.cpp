#include "GLEntityRenderer.h"
#include <glm\gtc\matrix_transform.hpp>

#define MVP_MATRIX 0

GLEntityRenderer::GLEntityRenderer()
{
	GLShader* shader = new GLShader("entity");
	shader->addAtribute("position");
	shader->addAtribute("normal");
	shader->addAtribute("texture");
	shader->compile();

	shader->allocateLocations(1);
	shader->setLocation(MVP_MATRIX, "mvp");
	setShader(shader);

	projectionMatrix = glm::perspective(70.0F, 720.0F/640.0F, 0.1F, 1000.0F);
	viewMatrix = glm::translate(glm::rotate(glm::mat4(1), test, glm::vec3(0, 1, 0)), glm::vec3(0, 0, -4));
}

void GLEntityRenderer::onRenderModel(Types::PlainModel* model)
{
	viewMatrix = glm::translate(glm::rotate(glm::rotate(glm::mat4(1), -0.4F, glm::vec3(1, 0, 0)), test, glm::vec3(0, 1, 0)), glm::vec3(0, -2, 0));
	test += 0.01F;
	getShader()->loadVector(projectionMatrix * viewMatrix, MVP_MATRIX);
}