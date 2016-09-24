#pragma once
#include "GLRenderer.h"

/* Renders the scenes entity's */
class GLEntityRenderer : public GLRenderer
{
public:
	GLEntityRenderer();
private:
	virtual void onRenderAll() {};
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);
	
	float test = 0;
};