#pragma once
#include "../Entities/DunoCamera.h"
#include "../GameUtil/Logger.h"
#include "Lighting/DunoLightManager.h"
#include "GLShader.h"
#include <vector>
using namespace std;
using namespace Duno::Types;

/* The renderer base class */
class GLRenderer
{
public:
	/* Renders all the objects */
	void render(vector<DunoGameObject*> models, DunoCamera* cam);
	void render(DunoCamera* cam) { render(m_models, cam); };

	/* Adds an object to the list to be rendered */
	void addModel(DunoGameObject* model) { m_models.push_back(model); }

	/* Sets the current projection matrix */
	virtual void setProjectionMatrix(const glm::mat4& matrix) { m_projection_matrix = matrix; }

	/* Update Lighting Data */
	void updateLights(DunoLightManager* light_manager);

	~GLRenderer() { delete m_shader; }
protected:
	/* Gets called when the scene is rendered */
	virtual void onRenderAll(DunoCamera* cam) = 0;

	/* Gets called when each object is rendered */
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam) = 0;

	/* Called When Lights Updated */
	virtual void onUpdateLights(DunoLightManager* light_manager) {};

	/* Sets the current shader */
	void setShader(GLShader* shader) { this->m_shader = shader; }

	/* Returns the current shader */
	GLShader* getShader() { return m_shader; }

	/* The current projection matrix */
	glm::mat4 m_projection_matrix;

	/* All the objects in the scene */
	vector<DunoGameObject*> m_models;
private:
	/* The current shader */
	GLShader* m_shader;
};