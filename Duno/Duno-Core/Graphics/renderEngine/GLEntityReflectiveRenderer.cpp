#include "GLEntityReflectiveRenderer.h"
#include "GLTextureLoader.h"
#include <iostream>
using namespace std;

/* Define all uniform location handles */
#define CUBE_MAP 6
#define CAMERA_POSITION 7

GLEntityReflectiveRenderer::GLEntityReflectiveRenderer(GLTexture* cubeMap):
	GLEntityRenderer("entity/reflective", 2),
	m_cube_map(cubeMap)
{
	/* Map all uniforms */
	getShader()->setLocation(CUBE_MAP, "cubeMap");
	getShader()->setLocation(CAMERA_POSITION, "cameraPosition");

	/* Load the cube map to texture unit 2 */
	getShader()->bind();
	getShader()->loadInt(2, CUBE_MAP);
	getShader()->unbind();
}

/* Extends Render Model Function */
void GLEntityReflectiveRenderer::addRenderModel(DunoGameObject* model, DunoCamera* cam)
{
	/* Bind the cube map texture */
	GLTextureLoader::bindTextureCube(m_cube_map, 2);
	getShader()->loadVector(cam->getPosition(), CAMERA_POSITION);
}