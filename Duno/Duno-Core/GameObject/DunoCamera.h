#pragma once
#include "DunoGameObject.h"

/* A camra that will set the view the scene will be rendered to */
class DunoCamera : public DunoGameObject
{
public:
	DunoCamera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
		DunoGameObject(NULL, NULL, position, rotation, scale) {}
	/* Updates a mouse look script for debug */
	void updateMouseLook(float xSensitivity, float ySensitivity, bool toggle = true);
	/* Updates a free flying script for debug */
	void updateFreeMove(float speed);
	/* Overides the default tranfromation matrix */
	virtual glm::mat4 getTransformationMatrix();
	/* Returns the cameras position */
	glm::vec3 getPosition() { return position; }
	void setPosition(glm::vec3 pos) { position = pos; }
	glm::vec3 getRotation() { return rotaiton; };
	void setRoation(glm::vec3 rot) { rotaiton = rot; }
private:
	/* Stores the last mouse position to calculate motion */
	glm::vec2 preMousePos;
};