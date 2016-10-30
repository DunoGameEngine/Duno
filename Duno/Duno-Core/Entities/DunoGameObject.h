#pragma once
#include "../Graphics/renderEngine/Types/PlainModel.h"
#include "../Graphics/renderEngine/Types/GLTexture.h"
#include "../Graphics/renderEngine/Types/Material/GLMaterial.h"
#include <glm\glm.hpp>
using namespace Duno::Graphics::RenderEngine::Types;
using namespace glm;

namespace Duno{namespace Types{

	/* Stores the default data for all objects that are in the scene */
	class DunoGameObject
	{
	public:
		DunoGameObject(PlainModel* model, GLMaterial* mat, vec3 position, vec3 rotation, vec3 scale) :
			model(model),
			mat(mat),
			position(position),
			rotaiton(rotaiton),
			scale(scale) {}

		/* Returns the transformations as a matrix */
		virtual mat4 getTransformationMatrix();

		/* Returns the model's ID */
		unsigned int getModelID() { return model->getVaoID(); }

		/* Returns the model's length */
		unsigned int getModelLegnth() { return model->getVaoLength(); }

		GLMaterial* getMateral() { return mat; }
		bool getIndexBuffer() { return model->getHasIndexBuffer(); }

		//Call when the entity is loaded
		virtual void OnLoadEntity() {};

		virtual void OnUpdateEntity() {};

		virtual void OnCloseEntity() {};

		glm::vec3 getPosition() { return position; }
		void setPosition(glm::vec3 pos) { position = pos; }
		void setMaterial(GLMaterial* m) { mat = m; }

	protected:

		/* Display Data */
		PlainModel* model;
		GLMaterial* mat;

		/* Transformation Data */
		vec3 position;
		vec3 rotaiton;
		vec3 scale;
	};
}}