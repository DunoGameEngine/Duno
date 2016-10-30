#pragma once
#include <vector>
using namespace std;

/* keeps track of the time and frame time in the game */
class GameTimer
{
public:
	/* Returns the time in milliseconds */
	static long currentTimeInMills();
	
	/* Returns how long the last frame took to render and/or update */
	static float getFrameTimeSeconds();
	
	/* Updates the time (called after every frame) */
	static void update();
private:
	/* Keeps the time when the last frame started */
	static long m_last_frame_time;
	
	/* Keeps how long the last frame took to render and/or update */
	static float m_delta;

	static vector<float> m_last;

	static float m_ad;
};
