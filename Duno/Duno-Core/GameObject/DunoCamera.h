#pragma once
#include "DunoGameObject.h"

class DunoCamera : public DunoGameObject
{
public:
	DunoCamera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
		DunoGameObject(NULL, NULL, position, rotation, scale) {}
	void updateMouseLook(float xSensitivity, float ySensitivity);
	void updateFreeMove(float speed);
	virtual glm::mat4 getTransformationMatrix();
	glm::vec3 getPosition() { return position; }
private:
	glm::vec2 preMousePos;
};