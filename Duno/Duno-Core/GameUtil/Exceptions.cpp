#include "Exceptions.h"
#include "Logger.h"

string defaultMessage()
{
	return "Duno Excetion:\nError occored within the '" + Logger::getSpace() + "' space\n";
}