#include "GLRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

void GLRenderer::render(vector<DunoGameObject*> models, DunoCamera* cam)
{
	m_shader->bind();
	onRenderAll(cam);
	for (DunoGameObject* object : models)
	{
		glBindVertexArray(object->getModelID());
		onRenderModel(object, cam);
		if (object->getIndexBuffer())
			glDrawElements(GL_TRIANGLES, object->getModelLegnth(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, object->getModelLegnth());
	}
	glBindVertexArray(0);
	m_shader->unbind();
}

/* Update Lighting Data */
void GLRenderer::updateLights(DunoLightManager* light_manager)
{
	/* Bind the shader as it will always use it */
	m_shader->bind();
	onUpdateLights(light_manager);
	m_shader->unbind();
}