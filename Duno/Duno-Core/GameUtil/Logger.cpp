#include "Logger.h"
#include "GameTimer.h"
#include <iostream>
using namespace std;

/* Allows the file to access the space stack and the last time */
vector<string> Logger::spaceStack;
long Logger::lastTime;
void Logger::init()
{
	lastTime = GameTimer::currentTimeInMills();
	setSpace("Log INIT");
	logln("Started Log");
	back();
}
string Logger::getSpace()
{
	/* if there is no space defined then default to 'NULL SPACE' */
	if (spaceStack.size() == 0)
		return "NULL SPACE";
	return spaceStack[spaceStack.size() - 1];
}
template<typename T> void Logger::log(T t)
{
	/* Outputs the time between logs, then the current space and then the message */
	cout << (int)(GameTimer::currentTimeInMills() - lastTime) << " [" << getSpace() << "] " << t;
	lastTime = GameTimer::currentTimeInMills();
}
template<typename T> void Logger::logln(T t)
{
	/* Logs then ends the line */
	log(t);
	cout << endl;
}