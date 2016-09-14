#pragma once

/* keeps track of the time and frame time in the game */
class GameTimer
{
public:
	/* Returns the time in milloseconds */
	static long currentTimeInMills();
	/* Returns how long the last frame took to render and or update */
	float getFrameTimeSeconds() { return delta; }
	/* Updates the times (called after every frame) */
	void update();
private:
	/* Keeps the time that the last frame started */
	long lastFrameTime;
	/* Keeps how long the last frame took to render and or update */
	float delta;
};