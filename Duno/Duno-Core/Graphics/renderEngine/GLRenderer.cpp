#include "GLRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

void GLRenderer::render(vector<DunoGameObject*> models, DunoCamera* cam)
{
	onRenderAll(cam);
	shader->bind();
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
	shader->unbind();
}