#include "Debug.h"
#include "Logger.h"
#ifdef _WIN32
#include <Windows.h>
#endif

struct Debug::NOTFOUND { NOTFOUND(NOTFOUND type, string msg) {} string msg = "Object not found error"; };
template<typename Type> void Debug::error(Type type, string mag)
{
	Logger::setSpace("ERROR");
	Logger::log(type.msg);
	Logger::log(" >> " + msg);
	Logger::back();
#ifdef _WIN32
	MessageBoxA(0, type.msg + "\n >> " + msg);
#endif
	exit(0);
}