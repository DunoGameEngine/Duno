#pragma once
#include "GLRenderer.h"
#include <vector>
using namespace std;

class GLMainRenderer
{
public:
	GLMainRenderer(DunoCamera* cam) : activeCamera(cam) {}
	void addRenderer(GLRenderer* renderer) { renderers.push_back(renderer); };
	GLRenderer* getRenderer(unsigned int index) { return renderers[index]; }
	
	void renderScene();
	void updateProjectionMatrix();
	~GLMainRenderer() { delete activeCamera; }
private:
	vector<GLRenderer*> renderers;
	DunoCamera* activeCamera;
};