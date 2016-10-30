#pragma once

/* Gets Info On The Display */
class DunoDisplayInfo
{
public:
	/* Set Display Size In Pixels */
	static void setSize(unsigned int w, unsigned int h) { width = w; height = h; resized = true; }
	/* Return Display Width In Pixels */
	static unsigned int getWidth() { return width; }
	/* Return Display Height In Pixels */
	static unsigned int getHeight() { return height; }

	/* Return If Display Resized */
	static bool hasResized() { if (resized) { resized = false; return true; } return false; }
private:
	/* Store Display's Data */
	static unsigned int width, height;
	static bool resized;
};