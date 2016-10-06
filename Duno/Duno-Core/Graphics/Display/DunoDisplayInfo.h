#pragma once

class DunoDisplayInfo
{
public:
	static void setSize(unsigned int w, unsigned int h) { width = w; height = h; resized = true; }
	static unsigned int getWidth() { return width; }
	static unsigned int getHeight() { return height; }

	static bool hasResized() { if (resized) { resized = false; return true; } return false; }
private:
	static unsigned int width, height;
	static bool resized;
};