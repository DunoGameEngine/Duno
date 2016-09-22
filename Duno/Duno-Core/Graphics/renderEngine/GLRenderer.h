#pragma once
#include <vector>
#include "Types\PlainModel.h"
#include "GLShader.h"
using namespace std;
using namespace Duno::Graphics::RenderEngine;

class GLRenderer
{
public:
	void render();
	void addModel(Types::PlainModel* model) { models.push_back(model); }
	~GLRenderer() { delete shader; }
protected:
	virtual void onRenderAll() = 0;
	virtual void onRenderModel(Types::PlainModel* model) = 0;

	void setShader(GLShader* shader) { this->shader = shader; }
	GLShader* getShader() { return shader; }
private:
	vector<Types::PlainModel*> models;
	GLShader* shader;
};