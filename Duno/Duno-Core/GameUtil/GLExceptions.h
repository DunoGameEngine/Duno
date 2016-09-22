#pragma once
#include "Exceptions.h"

class GLShaderCannotBeCreatedException : public DunoException
{
public:
	GLShaderCannotBeCreatedException() : DunoException() {}
	virtual string errorOut()
	{
		return defaultMessage() + "\nShaderCannotBeCreatedException";
	}
};

class GLShaderErrorException : public DunoException
{
public:
	GLShaderErrorException(string msg) : DunoException(), msg(msg) {}
	virtual string errorOut()
	{
		return defaultMessage() + "\nGLShaderErrorException\nError: " + msg;
	}
private:
	string msg;
};