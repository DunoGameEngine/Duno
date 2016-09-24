#pragma once
#include <glm\glm.hpp>

/* Handles mouse input ane motion */
class DunoMouse
{
public:
	/* Returns the mouses current position */
	static glm::vec2 getMousePosition() { return position; }

	/* Updates the mouse */
	static void update(glm::vec2 pos) { position = pos; }
private:
	/* Stores the mouse's current position */
	static glm::vec2 position;
};