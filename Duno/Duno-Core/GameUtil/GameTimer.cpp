#include "GameTimer.h"
#include <chrono>
using namespace std;

float GameTimer::delta;
long GameTimer::lastFrameTime;
/* Uses the c++11 library 'chrono' to get the current time */
long GameTimer::currentTimeInMills() 
{
	return chrono::system_clock::now().time_since_epoch() / chrono::milliseconds(1);
}

/* subtracts the time the current time with the time the last frame started and 
divides it by 1000 to convert it into seconds */
void GameTimer::update()
{
	long currentFrameTime = GameTimer::currentTimeInMills();
	if (lastFrameTime == 0) lastFrameTime = currentFrameTime;
	delta = (currentFrameTime - lastFrameTime) / 1000.0F;
	lastFrameTime = currentFrameTime;
}
