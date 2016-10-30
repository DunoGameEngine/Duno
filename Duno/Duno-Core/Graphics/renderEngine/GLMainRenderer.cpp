#include "GLMainRenderer.h"
#include "../Display/DunoDisplayInfo.h"
#include <glm/gtc/matrix_transform.hpp>

/* Renderer All */
void GLMainRenderer::renderScene()
{
	/* Deal with world lights */
	if (m_dirty_lights)
	{
		for (GLRenderer* renderer : m_renderers)
		{
			renderer->updateLights(m_light_manager);
		}
		m_dirty_lights = false;
	}

	/* Render the scene */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (GLRenderer* renderer : m_renderers)
	{
		renderer->render(m_active_camera);
	}
}

/* Set Up All Projection Matrices */
void GLMainRenderer::updateProjectionMatrix()
{
	float aspect = (float)DunoDisplayInfo::getWidth() / (float)DunoDisplayInfo::getHeight();
	glm::mat4 projectionMatrix = glm::perspective(70.0F, aspect, 0.1F, 1000.0F);
	for (GLRenderer* renderer : m_renderers)
	{
		renderer->setProjectionMatrix(projectionMatrix);
	}
}

/* Set Uses Depth Test */
void GLMainRenderer::setEnableDepthTest(bool flag)
{
	if (flag) glEnable(GL_DEPTH_TEST);
	else      glDisable(GL_DEPTH_TEST);
}