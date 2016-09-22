#include "GLRenderer.h"
#include <iostream>
using namespace std;

void GLRenderer::render()
{
	shader->bind();
	onRenderAll();
	for (Types::PlainModel* model : models)
	{
		glBindVertexArray(model->getVaoID());
		onRenderModel(model);
		glDrawElements(GL_TRIANGLES, model->getVaoLength(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}