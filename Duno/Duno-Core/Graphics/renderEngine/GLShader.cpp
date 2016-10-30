#include "GLShader.h"
#include "../GameUtil/GLExceptions.h"
#include "../Assets/FileSystem.h"
#include "../GameUtil/Logger.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

/* Adds an attribute before compile */
void GLShader::addAtribute(string attribute)
{
	if (m_attributes != NULL)
		m_attributes->push_back(attribute);
	else
		/* An attribute has been added after shader compile time */
		throw new GLShaderErrorException("Tried to load attribute after compiling it");
}

/* Check for errors after a OpenGL operation */
/* Currently disabled                        */
void errorCheck(GLuint shaderProgram, unsigned int type)
{
	GLint error = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderProgram);
		cerr << string(errorLog.begin(), errorLog.end()).c_str() << endl;
		//throw new GLShaderErrorException(/*string(errorLog.begin(), errorLog.end())*/"Error");
	}
}

/* Compiles a single shader file */
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

/* Start shader compile time */
void GLShader::compile()
{
	Logger::logln(LoggerTools::str("Shaders/" + m_name + "/shader.vs").c_str());
	
	/* Create an get the code of the shader */
	m_shader_program = glCreateProgram();
	string virtexCode = FileSystem::loadFile("Shaders/" + m_name + "/shader.vs").getData();
	string fragmentCode = FileSystem::loadFile("Shaders/" + m_name + "/shader.fs").getData();

	/* Compile each shader */
	m_shaders[0] = compileShader(virtexCode.c_str(), (GLuint)virtexCode.size(), GL_VERTEX_SHADER, m_shader_program);
	m_shaders[1] = compileShader(fragmentCode.c_str(), (GLuint)fragmentCode.size(), GL_FRAGMENT_SHADER, m_shader_program);
	for (unsigned int i = 0; i < 2; i++)
		glAttachShader(m_shader_program, m_shaders[i]);

	/* Bind the attributes */
	for (unsigned int i = 0; i < m_attributes->size(); i++)
		glBindAttribLocation(m_shader_program, i, m_attributes->at(i).c_str());
	delete m_attributes;

	/* Link and validate the shader */
	glLinkProgram(m_shader_program);
	//errorCheck(shaderProgram, GL_LINK_STATUS);
	glValidateProgram(m_shader_program);
	//errorCheck(shaderProgram, GL_VALIDATE_STATUS);

	/* Bind default texture units */
	glUseProgram(m_shader_program);
	glUniform1i(glGetUniformLocation(m_shader_program, "defuse"), 0);
	glUniform1i(glGetUniformLocation(m_shader_program, "bump"), 1);
	glUseProgram(0);
}

GLShader::~GLShader()
{
	for (unsigned int i = 0; i < sizeof(m_shaders) / sizeof(m_shaders[0]); i++)
	{
		glDetachShader(m_shader_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteShader(m_shader_program);

	delete m_locations;
	delete m_subroutines;
}