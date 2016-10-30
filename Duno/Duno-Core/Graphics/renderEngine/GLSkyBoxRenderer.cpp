#include "GLSkyBoxRenderer.h"
#include "GLTextureLoader.h"
#include "Types/Material/GLBasicMateralTypes.h"

/* Define all uniform location handles */
#define MVP_MATRIX 0

GLSkyBoxRenderer::GLSkyBoxRenderer(GLLoader* loader)
{
	GLShader* shader = new GLShader("skybox");
	/* Map all the attribute locations */
	shader->addAtribute("position");
	shader->compile();

	shader->allocateLocations(1);
	/* Set all the uniform locations */
	shader->setLocation(MVP_MATRIX, "mvp");
	setShader(shader);
}

/* Called When Rendering Each Model */
void GLSkyBoxRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLMaterialBasic* mat = static_cast<GLMaterialBasic*>(model->getMateral());
	GLTextureLoader::bindTextureCube(mat->getDeffuse(), 0);
	glm::mat4 matrix = cam->getTransformationMatrix();
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;

	getShader()->loadMatrix(m_projection_matrix * matrix, MVP_MATRIX);
}