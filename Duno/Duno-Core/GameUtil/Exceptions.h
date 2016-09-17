#pragma once
#include <exception>
#include <string>
using namespace std;
string defaultMessage();

class DunoException : public exception
{
public:
	virtual string errorOut() { return ""; };
};
class WrongFileTypeExcption : public DunoException
{
public:
	WrongFileTypeExcption(const char* type) : type(type) {}
	virtual string errorOut()
	{
		return defaultMessage() + "Error loading file type '" + type + "'";
	}
private:
	const char* type;
};