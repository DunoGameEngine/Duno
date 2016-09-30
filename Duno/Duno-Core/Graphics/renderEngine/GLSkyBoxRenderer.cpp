#include "GLSkyBoxRenderer.h"
#include "GLTextureLoader.h"

#define MVP_MATRIX 0

GLSkyBoxRenderer::GLSkyBoxRenderer(GLLoader* loader)
{
	GLShader* shader = new GLShader("skybox");
	shader->addAtribute("position");
	shader->compile();

	shader->allocateLocations(1);
	shader->setLocation(MVP_MATRIX, "mvp");
	setShader(shader);
}

void GLSkyBoxRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLTextureLoader::bindTextureCube(model->getMateral()->getDefuse(), 0);
	glm::mat4 matrix = cam->getTransformationMatrix();
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;

	getShader()->loadMatrix(projectionMatrix * matrix, MVP_MATRIX);
}