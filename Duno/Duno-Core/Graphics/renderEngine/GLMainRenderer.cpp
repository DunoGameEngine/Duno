#include "GLMainRenderer.h"
#include "../Display/DunoDisplayInfo.h"
#include <glm\gtc\matrix_transform.hpp>

void GLMainRenderer::renderScene()
{
	for (GLRenderer* renderer : renderers)
		renderer->render(activeCamera);
}
void GLMainRenderer::updateProjectionMatrix()
{
	float aspect = (float)DunoDisplayInfo::getWidth() / (float)DunoDisplayInfo::getHeight();
	glm::mat4 projectionMatrix = glm::perspective(70.0F, aspect, 0.1F, 1000.0F);
	for (GLRenderer* renderer : renderers)
		renderer->setProjectionMatrix(projectionMatrix);
}