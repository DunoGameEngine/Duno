#include "GLShader.h"
#include "../GameUtil/GLExceptions.h"
#include "../Assets/FileSystem.h"
#include <fstream>
#include <vector>

void GLShader::addAtribute(string attribute)
{
	if (attributes != NULL)
		attributes->push_back(attribute);
	else
		throw new GLShaderErrorException("Tryed to load attribute after compiling it");
}

void errorCheck(GLuint shaderProgram, unsigned int type)
{
	GLint error = 0;
	glGetShaderiv(shaderProgram, type, &error);
	if (error == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderProgram);
		throw new GLShaderErrorException(string(errorLog.begin(), errorLog.end()));
	}
}
GLuint compileShader(const char* src, GLuint length, GLenum shaderType, GLuint shaderProgram)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		throw new GLShaderCannotBeCreatedException();

	const GLchar* sss[1];
	GLint ssl[1];
	sss[0] = src;
	ssl[0] = length;

	glShaderSource(shader, 1, sss, ssl);
	glCompileShader(shader);

	//errorCheck(shaderProgram, GL_COMPILE_STATUS);
	return shader;
}
void GLShader::compile()
{
	shaderProgram = glCreateProgram();
	string virtexCode = FileSystem::loadFile("Shaders/" + name + "/shader.vs").getData();
	string fragmentCode = FileSystem::loadFile("Shaders/" + name + "/shader.fs").getData();

	shaders[0] = compileShader(virtexCode.c_str(), (GLuint)virtexCode.size(), GL_VERTEX_SHADER, shaderProgram);
	shaders[1] = compileShader(fragmentCode.c_str(), (GLuint)fragmentCode.size(), GL_FRAGMENT_SHADER, shaderProgram);
	for (unsigned int i = 0; i < 2; i++)
		glAttachShader(shaderProgram, shaders[i]);

	for (unsigned int i = 0; i < attributes->size(); i++)
		glBindAttribLocation(shaderProgram, i, attributes->at(i).c_str());
	delete attributes;

	glLinkProgram(shaderProgram);
	//errorCheck(shaderProgram, GL_LINK_STATUS);
	glValidateProgram(shaderProgram);
	//errorCheck(shaderProgram, GL_VALIDATE_STATUS);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "defuse"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "bump"), 1);
	glUseProgram(0);
}

GLShader::~GLShader()
{
	for (unsigned int i = 0; i < sizeof(shaders) / sizeof(shaders[0]); i++)
	{
		glDetachShader(shaderProgram, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteShader(shaderProgram);
}