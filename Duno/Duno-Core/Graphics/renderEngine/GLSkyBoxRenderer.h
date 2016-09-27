#pragma once
#include "GLRenderer.h"
#include "GLLoader.h"

class GLSkyBoxRenderer : public GLRenderer
{
public:
	GLSkyBoxRenderer(GLLoader* loader);
private:
	virtual void onRenderAll(DunoCamera* cam) {}
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);
};