#pragma once
#include "../OpenGL/GL.h"
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
using namespace std;

/* Represents an handles a OpenGL shader */
class GLShader
{
public:
	GLShader(string name) : name(name), attributes(new vector<string>()) {};
	void compile();
	~GLShader();

	/* Allocates an amount of space to store the uniform locations */
	void allocateLocations(unsigned int size) { locations = new GLuint[size]; }
	/* Assighens a location */
	void setLocation(unsigned int location, string uniform) { locations[location] = glGetUniformLocation(shaderProgram, uniform.c_str()); };
	/* Adds an atribute before compile */
	void addAtribute(string attribute);
	/* Binds this shader */
	void bind() { glUseProgram(shaderProgram); }

	/* Loads a matrix to a uniform */
	void loadVector(const glm::mat4& matrix, unsigned int location) { glUniformMatrix4fv(locations[location], 1, false, glm::value_ptr(matrix)); };
private:
	GLuint shaderProgram;
	GLuint shaders[2];
	GLuint* locations;

	string name;
	vector<string>* attributes;
};