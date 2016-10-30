#include "GLEntityRenderer.h"
#include "GLTextureLoader.h"
#include "Types/Material/GLBasicMateralTypes.h"
#include "../GameUtil/GameTimer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

/* Define all uniform location handles */
#define MVP_MATRIX         0
#define M_MATRIX           1
#define POINT_LIGHTPOS     2
#define POINT_LIGHTCOLOUR  3
#define POINT_LENGTH       4
#define DIR_LIGHTDIR       5
#define DIR_LENGTH         6
#define CAM_POSITION       7
#define AMBIENT_LIGHT      8
#define SHININESS          9
#define LIGHT_EMITTED      10
#define SPEC_MAP           11

/* Define all subroutines */
#define SUB_BASIC   0
#define SUB_BUMPED  1
#define SUB_FULL    2

/* Define how many lights can be in the scene at once */
#define LIGHT_SIZE 4

GLEntityRenderer::GLEntityRenderer(string shaderName, unsigned int locationExt)
{
	GLShader* shader = new GLShader(shaderName);
	/* Map all the attribute locations */
	shader->addAtribute("position");
	shader->addAtribute("texture");
	shader->addAtribute("normal");
	shader->addAtribute("tangent");
	shader->compile();

	shader->allocateLocations(12 + locationExt);
	/* Set all the uniform locations */
	shader->setLocation(MVP_MATRIX, "mvp");
	shader->setLocation(M_MATRIX, "m");
	shader->setLocation(POINT_LIGHTPOS, "point_lightPos");
	shader->setLocation(POINT_LIGHTCOLOUR, "point_lightColour");
	shader->setLocation(POINT_LENGTH, "point_length");
	shader->setLocation(DIR_LIGHTDIR, "dir_lightDir");
	shader->setLocation(DIR_LENGTH, "dir_length");
	shader->setLocation(CAM_POSITION, "cam_position");
	shader->setLocation(AMBIENT_LIGHT, "ambient_light");
	shader->setLocation(SHININESS, "shininess");
	shader->setLocation(LIGHT_EMITTED, "light_emitted");
	shader->setLocation(SPEC_MAP, "spec_map");

	shader->allocateSubroutines(3);
	shader->setSubroutine(SUB_BASIC, GL_FRAGMENT_SHADER, "basic");
	shader->setSubroutine(SUB_BUMPED, GL_FRAGMENT_SHADER, "bumped");
	shader->setSubroutine(SUB_FULL, GL_FRAGMENT_SHADER, "full");

	setShader(shader);
	shader->bind();
	getShader()->loadInt(2, SPEC_MAP);

	getShader()->loadInt(LIGHT_SIZE, POINT_LENGTH);
	getShader()->loadInt(LIGHT_SIZE, DIR_LENGTH);
	shader->unbind();
}

void GLEntityRenderer::onRenderAll(DunoCamera* cam) {}

/* Called When Rendering Each Model */
void GLEntityRenderer::onRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLMaterialBasic* basic = static_cast<GLMaterialBasic*>(model->getMateral());
	getShader()->loadSubroutine(GL_FRAGMENT_SHADER, basic->getType());
	
	GLTextureLoader::bindTexture(basic->getDeffuse(), 0);
	getShader()->loadFloat(basic->getSpecularLight(), SHININESS);
	getShader()->loadFloat(basic->getLightEmitted(), LIGHT_EMITTED);

	if (model->getMateral()->getType() >= DUNOMETRRIAL_BUMPED)
	{
		GLMaterialBumped* bumped = static_cast<GLMaterialBumped*>(model->getMateral());
		GLTextureLoader::bindTexture(bumped->getNormalMap(), 1);
	}
	if (model->getMateral()->getType() >= DUNOMETRRIAL_FULL)
	{
		GLMaterialFull* full = static_cast<GLMaterialFull*>(model->getMateral());
		GLTextureLoader::bindTexture(full->getSpecularMap(), 2);
	}

	/* Load uniforms */
	getShader()->loadMatrix(m_projection_matrix * cam->getTransformationMatrix() * model->getTransformationMatrix(), MVP_MATRIX);
	getShader()->loadMatrix(model->getTransformationMatrix(), M_MATRIX);
	getShader()->loadVector(cam->getPosition(), CAM_POSITION);
	
	/* Do shader extension */
	addRenderModel(model, cam);
}

/* Called When Lights Updated */
void GLEntityRenderer::onUpdateLights(DunoLightManager* light_manager)
{
	/* Get all the light's data */
	LightOut light_data = light_manager->getLightData(LIGHT_SIZE);

	/* Load point lights */
	getShader()->loadVectorArray(light_data.m_point_positions, LIGHT_SIZE, POINT_LIGHTPOS);
	getShader()->loadVectorArray(light_data.m_point_colours, LIGHT_SIZE, POINT_LIGHTCOLOUR);

	/* Load the ambient light value */
	getShader()->loadVector(light_manager->getAmbientLight(), AMBIENT_LIGHT);
}
