#pragma once
#include <glm\glm.hpp>

/* Handles Mouse Input and Motion */
class DunoMouse
{
public:
	/* Returns the mouses current position */
	static glm::vec2 getMousePosition() { return position; }
	/* Updates the mouse position */
	static void update(glm::vec2 pos) { position = pos; }
	/* Sets a click value */
	static void setClick(bool clicked, unsigned int index) { clickInfo[index] = clicked; }

	static void setDisabled(bool flag) { disabled = flag; }
	static bool isDisabled() { return disabled; }

	/* Returns if the left mouse button it down */
	static bool isLeftMouseDown() { return clickInfo[0]; }
	/* Returns if the right mouse button it down */
	static bool isRightMouseDown() { return clickInfo[0]; }
	/* Returns if the middle mouse button it down */
	static bool isMiddleMouseDown() { return clickInfo[0]; }
private:
	/* Stores the mouse's current position */
	static glm::vec2 position;
	/* Stores click info */
	static bool clickInfo[3];
	/* Stores if the mouse has been grabbed */
	static bool disabled;
};