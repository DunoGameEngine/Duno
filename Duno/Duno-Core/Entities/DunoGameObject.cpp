#include "DunoGameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include<cmath>

/* Defines PI */
#define M_PI 3.14159265358979323846
/* Converts from deg to rad */
#define TORAD(deg) (float)(deg * M_PI) / 180.0F

glm::mat4 DunoGameObject::getTransformationMatrix()
{
	glm::mat4 matrix = glm::mat4(1);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, TORAD(rotaiton.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, TORAD(rotaiton.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, TORAD(rotaiton.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);
	return matrix;
}