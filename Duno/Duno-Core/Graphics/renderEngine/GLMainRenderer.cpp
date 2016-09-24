#include "GLMainRenderer.h"
#include <glm\gtc\matrix_transform.hpp>

void GLMainRenderer::renderScene()
{
	for (GLRenderer* renderer : renderers)
		renderer->render(activeCamera);
}
void GLMainRenderer::updateProjectionMatrix()
{
	glm::mat4 projectionMatrix = glm::perspective(70.0F, 1280.0F / 720.0F, 0.1F, 1000.0F);
	for (GLRenderer* renderer : renderers)
		renderer->setProjectionMatrix(projectionMatrix);
}