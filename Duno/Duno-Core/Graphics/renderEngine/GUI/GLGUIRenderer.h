#pragma once
#include "../GLRenderer.h"

class GLGUIRenderer : public GLRenderer
{
public:
	GLGUIRenderer();
	virtual void setProjectionMatrix(const glm::mat4& matrix);
private:
	void onRenderAll(DunoCamera* cam) {}
	void onRenderModel(DunoGameObject* model, DunoCamera* cam);
};