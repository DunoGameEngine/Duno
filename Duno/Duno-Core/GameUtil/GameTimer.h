#pragma once

/* keeps track of the time and frame time in the game */
class GameTimer
{
public:
	/* Returns the time in milloseconds */
	static long currentTimeInMills();
	
	/* Returns how long the last frame took to render and/or update */
	static float getFrameTimeSeconds() { return delta; }
	
	/* Updates the time (called after every frame) */
	static void update();
private:
	/* Keeps the time when the last frame started */
	static long lastFrameTime;
	
	/* Keeps how long the last frame took to render and/or update */
	static float delta;
};
