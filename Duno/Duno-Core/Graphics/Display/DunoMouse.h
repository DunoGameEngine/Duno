#pragma once
#include <glm\glm.hpp>

/* Handles mouse input ane motion */
class DunoMouse
{
public:
	/* Returns the mouses current position */
	static glm::vec2 getMousePosition() { return position; }
	/* Returns the mouses movement */
	static glm::vec2 getMouseMotion() { glm::vec2 test = position - prePosition; prePosition = position; return test; }

	/* Updates the mouse */
	static void update(glm::vec2 pos) { position = pos; }
private:
	/* Stores the mouse's current position */
	static glm::vec2 position;
	/* Stores the mouse's last position */
	static glm::vec2 prePosition;
};