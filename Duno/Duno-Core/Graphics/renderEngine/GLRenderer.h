#pragma once
#include <vector>
#include "../GameObject/DunoCamera.h"
#include "../GameUtil/Logger.h"
#include "GLShader.h"
using namespace std;
using namespace Duno::Graphics::RenderEngine;

/* The renderer base class */
class GLRenderer
{
public:
	/* Renders all the objects */
	void render(vector<DunoGameObject*> models, DunoCamera* cam);
	void render(DunoCamera* cam) { render(models, cam); };
	/* Adds an object to the list to be rendered */
	void addModel(DunoGameObject* model) { models.push_back(model); }
	/* Sets the current projection matrix */
	virtual void setProjectionMatrix(const glm::mat4& matrix) { projectionMatrix = matrix; }
	~GLRenderer() { delete shader; }
protected:
	/* Gets called when the scene is rendered */
	virtual void onRenderAll(DunoCamera* cam) = 0;
	/* Gets called when each object is rendered */
	virtual void onRenderModel(DunoGameObject* model, DunoCamera* cam) = 0;

	/* Sets the current shader */
	void setShader(GLShader* shader) { this->shader = shader; }
	/* Returns the current shader */
	GLShader* getShader() { return shader; }
	/* The current projection matrix */
	glm::mat4 projectionMatrix;
	/* All the objects in the scene */
	vector<DunoGameObject*> models;
private:
	/* The current shader */
	GLShader* shader;
};