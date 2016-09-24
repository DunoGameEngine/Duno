#include "GLRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

void GLRenderer::render(DunoCamera* cam)
{
	shader->bind();
	onRenderAll();
	for (DunoGameObject* object : models)
	{
		glBindVertexArray(object->getModelID());
		GLTextureLoader::bindTexture(object->getMateral()->getDefuse(), 0);
		GLTextureLoader::bindTexture(object->getMateral()->getBump(), 1);
		onRenderModel(object, cam);
		glDrawElements(GL_TRIANGLES, object->getModelLegnth(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}