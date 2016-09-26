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
		GLTextureLoader::bindTexture(object->getMateral()->getDefuse(), 0);
		GLTextureLoader::bindTexture(object->getMateral()->getBump(), 1);
		onRenderModel(object, cam);
		glDrawElements(GL_TRIANGLES, object->getModelLegnth(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
	shader->unbind();
}