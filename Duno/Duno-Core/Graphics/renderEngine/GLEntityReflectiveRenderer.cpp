#include "GLEntityReflectiveRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

#define CUBE_MAP 6
#define CAMERA_POSITION 7

GLEntityReflectiveRenderer::GLEntityReflectiveRenderer(GLTexture* cubeMap):
	GLEntityRenderer("entity/reflective", 2),
	cubeMap(cubeMap)
{
	getShader()->setLocation(CUBE_MAP, "cubeMap");
	getShader()->setLocation(CAMERA_POSITION, "cameraPosition");

	getShader()->bind();
	getShader()->loadInt(2, CUBE_MAP);
	getShader()->unbind();
}

void GLEntityReflectiveRenderer::addRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	GLTextureLoader::bindTextureCube(cubeMap, 2);
	getShader()->loadVector(cam->getPosition(), CAMERA_POSITION);
}