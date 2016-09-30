#pragma once
#include "GLRenderer.h"

/* Renders the scenes entity's */
class GLEntityRenderer : public GLRenderer
{
public:
	GLEntityRenderer(string shaderName, unsigned int locationExt);
	GLEntityRenderer() : GLEntityRenderer("entity", 0) {}
private:
	virtual void onRenderAll(DunoCamera* cam);
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);
	virtual void addRenderModel(DunoGameObject* model, DunoCamera* cam) {}
	
	float test = 0;
	GLTexture* shadowMap;
};