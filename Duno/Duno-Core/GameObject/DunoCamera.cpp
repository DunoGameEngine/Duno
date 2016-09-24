#include "DunoCamera.h"
#include "../Graphics/Display/DunoMouse.h"
#include "../Graphics/Display/DunoKeyboard.h"
#include "../GameUtil/GameTimer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
using namespace std;

/* Defines PI */
#define M_PI 3.14159265358979323846
/* Converts from deg to rad */
#define TORAD(deg) (float)(deg * M_PI) / 180.0F

void DunoCamera::updateMouseLook(float xSensitivity, float ySensitivity)
{
	glm::vec2 pos = DunoMouse::getMousePosition();
	glm::vec2 motion = pos - preMousePos;
	preMousePos = pos;
	rotaiton += glm::vec3(motion.y*ySensitivity, motion.x*xSensitivity, 0);
}
void DunoCamera::updateFreeMove(float speed)
{
	float rot = rotaiton.y;

	float gameSpeed = GameTimer::getFrameTimeSeconds() * speed;
	float x = sin(TORAD(rot)) * gameSpeed;
	float z = cos(TORAD(rot)) * gameSpeed;
	if (DunoKeyboard::isKeyDown(DUNO_KEY_W)) { position.x -= x; position.z += z; }
	if (DunoKeyboard::isKeyDown(DUNO_KEY_S)) { position.x += x; position.z -= z; }
	rot -= 90;
	x = sin(TORAD(rot)) * gameSpeed;
	z = cos(TORAD(rot)) * gameSpeed;
	if (DunoKeyboard::isKeyDown(DUNO_KEY_A)) { position.x -= x; position.z += z; }
	if (DunoKeyboard::isKeyDown(DUNO_KEY_D)) { position.x += x; position.z -= z; }

	if (DunoKeyboard::isKeyDown(DUNO_KEY_SPACE)) { position.y -= gameSpeed; }
	if (DunoKeyboard::isKeyDown(DUNO_KEY_LEFT_SHIFT)) { position.y += gameSpeed; }
}

glm::mat4 DunoCamera::getTransformationMatrix()
{
	glm::mat4 matrix = glm::mat4(1);
	matrix = glm::rotate(matrix, TORAD(rotaiton.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, TORAD(rotaiton.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, TORAD(rotaiton.z), glm::vec3(0, 0, 1));
	matrix = glm::translate(matrix, position);
	matrix = glm::scale(matrix, scale);
	return matrix;
}