#include "GLGUIRenderer.h"
#include "../GLTextureLoader.h"
#include "../GameObject/GUI/DunoGUIElement.h"

#define M_MATRIX 0

GLGUIRenderer::GLGUIRenderer()
{
	GLShader* shader = new GLShader("gui");
	shader->addAtribute("position");
	shader->compile();

	shader->allocateLocations(1);
	shader->setLocation(M_MATRIX, "m");
	setShader(shader);
}

void GLGUIRenderer::setProjectionMatrix(const glm::mat4& matrix)
{
	projectionMatrix = matrix;
	for (DunoGameObject* object : models)
		static_cast<DunoGUIElement*>(object)->update();
}

void GLGUIRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLTextureLoader::bindTexture(model->getMateral()->getDefuse(), 0);
	getShader()->loadMatrix(model->getTransformationMatrix(), M_MATRIX);
}