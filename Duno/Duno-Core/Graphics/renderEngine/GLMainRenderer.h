#pragma once
#include "GLRenderer.h"
#include <vector>
using namespace std;

/* Manage All Renderer Types */
class GLMainRenderer
{
public:
	GLMainRenderer(DunoCamera* cam) :
		m_active_camera(cam),
		m_light_manager(new DunoLightManager()),
		m_dirty_lights(true) {}
	
	/* Add Renderer Type */
	inline void addRenderer(GLRenderer* renderer) { m_renderers.push_back(renderer); };

	/* Return Renderer By ID */
	inline GLRenderer* getRenderer(unsigned int index) { return m_renderers[index]; }
	
	/* Renderer All */
	void renderScene();

	/* Set Up All Projection Matrices */
	void updateProjectionMatrix();
	~GLMainRenderer() { delete m_active_camera; }
	
	/* Set Uses Depth Test */
	void setEnableDepthTest(bool flag);

	/* Add Light To World */
	inline void addLight(Light* light) { m_light_manager->addLight(light); m_dirty_lights = true; }

	/* Set Ambient Light Value */
	inline void setAmbientLight(glm::vec3 light) { m_light_manager->setAmbientLight(light); }

	void setDirty() { m_dirty_lights = true; }
private:
	/* List Of Renderer Types */
	vector<GLRenderer*> m_renderers;

	/* Currently Renderer-able Camera */
	DunoCamera* m_active_camera;

	/* Manage World Lights */
	DunoLightManager* m_light_manager;

	/* True If Lights Have Updated */
	bool m_dirty_lights;
};