#pragma once
#include "GLEntityRenderer.h"

class GLEntityReflectiveRenderer : public GLEntityRenderer
{
public:
	GLEntityReflectiveRenderer(GLTexture* cubeMap);
	~GLEntityReflectiveRenderer() { delete cubeMap; }
private:
	virtual void addRenderModel(DunoGameObject* model, DunoCamera* cam);
	GLTexture* cubeMap;
};
