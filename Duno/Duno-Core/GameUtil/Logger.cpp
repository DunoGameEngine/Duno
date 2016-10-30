#include "Logger.h"
#include "GameTimer.h"
#include <iostream>
using namespace std;

/* Allows the file to access the space stack and the last time */
vector<string> Logger::m_space_stack;
long Logger::m_last_time;
void Logger::init()
{
	m_last_time = GameTimer::currentTimeInMills();
	setSpace("Log INIT");
	logln("Started Log");
	back();
}
string Logger::getSpace()
{
	/* if there is no space defined then default to 'NULL SPACE' */
	if (m_space_stack.size() == 0)
		return "NULL SPACE";
	return m_space_stack[m_space_stack.size() - 1];
}
template<typename T> void Logger::log(T t)
{
	/* Outputs the time between logs, then the current space and then the message */
	cout << (int)(GameTimer::currentTimeInMills() - m_last_time) << " [" << getSpace() << "] " << t;
	m_last_time = GameTimer::currentTimeInMills();
}
template<typename T> void Logger::logln(T t)
{
	/* Logs then ends the line */
	log(t);
	cout << endl;
}