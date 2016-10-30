#pragma once
#include "GLEntityRenderer.h"

/* Render Entity's With Reflections, Extends Entity Renderer */
class GLEntityReflectiveRenderer : public GLEntityRenderer
{
public:
	/* Constructor, Parse In Cube Map To Reflect */
	GLEntityReflectiveRenderer(GLTexture* cubeMap);
	~GLEntityReflectiveRenderer() { delete m_cube_map; }
private:
	/* Extends Render Model Function */
	virtual void addRenderModel(DunoGameObject* model, DunoCamera* cam);

	/* Stores The Reflection Texture */
	GLTexture* m_cube_map;
};
