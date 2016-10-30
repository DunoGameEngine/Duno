#pragma once
#include "GLRenderer.h"

/* Renders the scenes entity's */
class GLEntityRenderer : public GLRenderer
{
public:
	/* Parse In The Name Of The Shader's Files And The Uniform Extension Size */
	GLEntityRenderer(string shaderName, unsigned int locationExt);
	GLEntityRenderer() : GLEntityRenderer("entity", 0) {}
private:
	/* Called When Rendering All Entity's */
	virtual void onRenderAll(DunoCamera* cam);

	/* Called When Rendering Each Model */
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);

	/* Called When Finished Rendering Each Model */
	virtual void addRenderModel(DunoGameObject* model, DunoCamera* cam) {}

	/* Called When Lights Updated */
	virtual void onUpdateLights(DunoLightManager* light_manager);
};