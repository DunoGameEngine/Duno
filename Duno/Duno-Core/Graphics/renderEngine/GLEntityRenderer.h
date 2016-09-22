#pragma once
#include "GLRenderer.h"

class GLEntityRenderer : public GLRenderer
{
public:
	GLEntityRenderer();
private:
	virtual void onRenderAll() {};
	virtual void onRenderModel(Types::PlainModel* model);

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	float test = 0;
};