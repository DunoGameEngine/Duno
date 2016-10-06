#pragma once
#include "GLRenderer.h"
#include "GLLoader.h"
using namespace Duno::Graphics::RenderEngine;

class GLSkyBoxRenderer : public GLRenderer
{
public:
	GLSkyBoxRenderer(GLLoader* loader);
private:
	virtual void onRenderAll(DunoCamera* cam) {}
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);
};