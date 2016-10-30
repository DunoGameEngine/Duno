#pragma once
#include "GLRenderer.h"

/*                                      */
/*                                      */
/*                UNUSED                */
/*                                      */
/*                                      */

class GLShadowRenderer : public GLRenderer
{
public:
	GLShadowRenderer();
	~GLShadowRenderer() { delete m_shadow_cam; }
	glm::mat4 getShadowMatrix() { return m_shadow_projection_matix * m_shadow_cam->getTransformationMatrix(); }
private:
	virtual void onRenderAll(DunoCamera* cam) {}
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam);

	glm::mat4 m_shadow_projection_matix;
	DunoCamera* m_shadow_cam;
};