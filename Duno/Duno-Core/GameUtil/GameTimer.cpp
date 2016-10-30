#include "GameTimer.h"
#include <chrono>
using namespace std;

#define SMOOTHING 10

float GameTimer::m_delta;
long GameTimer::m_last_frame_time;
vector<float> GameTimer::m_last;
float GameTimer::m_ad;
/* Uses the c++11 library 'chrono' to get the current time */
long GameTimer::currentTimeInMills() 
{
	return (long)(chrono::system_clock::now().time_since_epoch() / chrono::milliseconds(1));
}

/* subtracts the time the current time with the time the last frame started and 
divides it by 1000 to convert it into seconds */
void GameTimer::update()
{
	long currentFrameTime = GameTimer::currentTimeInMills();
	if (m_last_frame_time == 0) m_last_frame_time = currentFrameTime;
	m_delta = (currentFrameTime - m_last_frame_time) / 1000.0F;
	m_last_frame_time = currentFrameTime;

	/* Store the last *SMOOTHING* delta times recorded */
	m_last.push_back(m_delta);
	if (m_last.size() >= SMOOTHING)
		m_last.erase(m_last.begin());

	/* Calculate the average */
	m_ad = 0;
	for (unsigned int i = 0; i < m_last.size(); i++)
		m_ad += m_last[i];
	m_ad /= m_last.size();
}

float GameTimer::getFrameTimeSeconds()
{
	return m_ad;
}