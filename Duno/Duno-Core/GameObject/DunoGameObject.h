#pragma once
#include "../Graphics/renderEngine/Types/PlainModel.h"
#include "../Graphics/renderEngine/Types/GLTexture.h"
#include <glm\glm.hpp>
using namespace Duno::Graphics::RenderEngine::Types;

/* Stores the default data for all objects that are in the scene */
class DunoGameObject
{
public:
	DunoGameObject(PlainModel* model, GLMateral* mat, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
		model(model),
		mat(mat),
		position(position),
		rotaiton(rotaiton),
		scale(scale) {}
	/* Returns the tranformations as a matrix */
	virtual glm::mat4 getTransformationMatrix();
	/* Returns the model's ID */
	unsigned int getModelID() { return model->getVaoID(); }
	/* Returns the model's legnth */
	unsigned int getModelLegnth() { return model->getVaoLength(); }
	GLMateral* getMateral() { return mat; }
protected:
	/* Display Data */
	PlainModel* model;
	GLMateral* mat;
	/* Transformation Data */
	glm::vec3 position;
	glm::vec3 rotaiton;
	glm::vec3 scale;
};