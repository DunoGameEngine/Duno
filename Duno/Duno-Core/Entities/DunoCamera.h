#pragma once
#include "DunoGameObject.h"

namespace Duno {namespace Types {
		/* A camera that will set the view the scene will be rendered to */
		class DunoCamera : public DunoGameObject
		{
		public:

			DunoCamera(vec3 position, vec3 rotation, vec3 scale) :
				DunoGameObject(NULL, NULL, position, rotation, scale) {}

			/* Updates a mouse look script for debug */
			void updateMouseLook(float xSensitivity, float ySensitivity, bool toggle = true);

			/* Updates a free flying script for debug */
			void updateFreeMove(float speed);

			/* Overrides the default transformation matrix */
			virtual mat4 getTransformationMatrix();

			/* Returns the cameras position */
			vec3 getPosition() { return position; }

			/* Set position of the camera */
			void setPosition(vec3 pos) { position = pos; }

			/* Return the rotation of the camera */
			vec3 getRotation() { return rotaiton; };

			/* Change rotation of the camera */
			void setRoation(vec3 rot) { rotaiton = rot; }

		private:
			/* Stores the last mouse position to calculate motion */
			vec2 preMousePos;
		};
}}