#pragma once
#include "GLRenderer.h"
#include "GLLoader.h"
using namespace Duno::Graphics::RenderEngine;

/* Render Skybox */
class GLSkyBoxRenderer : public GLRenderer
{
public:
	GLSkyBoxRenderer(GLLoader* loader);
private:
	/* Called When All Are Rendered */
	virtual void onRenderAll(DunoCamera* cam) {}

	/* Called When Each Model Rendered */
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);
};