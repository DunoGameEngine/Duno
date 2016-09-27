#include "GLEntityReflectiveRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

#define MVP_MATRIX 0
#define POINT_LIGHTPOS 1
#define POINT_LIGHTCOLOUR 2
#define POINT_LENGTH 3
#define DIR_LIGHTDIR 4
#define DIR_LENGTH 5
#define CUBE_MAP 6
#define CAMERA_POSITION 7

GLEntityReflectiveRenderer::GLEntityReflectiveRenderer(GLTexture* cubeMap):
	cubeMap(cubeMap)
{
	GLShader* shader = new GLShader("entity/reflective");
	shader->addAtribute("position");
	shader->addAtribute("texture");
	shader->addAtribute("normal");
	shader->compile();

	shader->allocateLocations(7);
	shader->setLocation(MVP_MATRIX, "mvp");
	shader->setLocation(POINT_LIGHTPOS, "point_lightPos");
	shader->setLocation(POINT_LIGHTCOLOUR, "point_lightColour");
	shader->setLocation(POINT_LENGTH, "point_length");
	shader->setLocation(DIR_LIGHTDIR, "dir_lightDir");
	shader->setLocation(DIR_LENGTH, "dir_length");
	shader->setLocation(CUBE_MAP, "cubeMap");
	shader->setLocation(CAMERA_POSITION, "cameraPosition");
	setShader(shader);

	shader->bind();
	shader->loadInt(2, CUBE_MAP);
	shader->unbind();
}

void GLEntityReflectiveRenderer::addRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLTextureLoader::bindTextureCube(cubeMap, 2);
	getShader()->loadVector(cam->getPosition(), CAMERA_POSITION);
}