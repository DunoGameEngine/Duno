#pragma once
#include "GLRenderer.h"

class GLShadowRenderer : public GLRenderer
{
public:
	GLShadowRenderer();
	~GLShadowRenderer() { delete shadow_cam; }
	glm::mat4 getShadowMatrix() { return shadow_projectionMatix * shadow_cam->getTransformationMatrix(); }
private:
	virtual void onRenderAll(DunoCamera* cam) {}
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);

	glm::mat4 shadow_projectionMatix;
	DunoCamera* shadow_cam;
};