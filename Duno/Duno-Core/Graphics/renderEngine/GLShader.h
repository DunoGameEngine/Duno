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
	/* Expands the current uniform locations storage spcae */
	void expandeLoactions(unsigned int from, unsigned int to) { GLuint* loc = new GLuint[to]; for (unsigned int i = 0; i < from; i++) loc[i] = locations[i]; delete locations; locations = loc; }
	/* Assighens a location */
	void setLocation(unsigned int location, string uniform) { locations[location] = glGetUniformLocation(shaderProgram, uniform.c_str()); };
	/* Adds an atribute before compile */
	void addAtribute(string attribute);
	/* Binds this shader */
	void bind() { glUseProgram(shaderProgram); }
	/* Unbinds the current shader */
	void unbind() { glUseProgram(0); }

	/* Converts a vector array to a GLFloat array */
	GLfloat* toArray(glm::vec3* vectorArray, unsigned int arraySize) { GLfloat* fa = new GLfloat[arraySize * 3]; for (unsigned int i = 0; i < arraySize; i++) { fa[i * 3] = vectorArray[i].x; fa[(i * 3) + 1] = vectorArray[i].y; fa[(i * 3) + 2] = vectorArray[i].z; } return fa; }

	/* Loads a matrix to a uniform */
	void loadMatrix(const glm::mat4& matrix, unsigned int location) { glUniformMatrix4fv(locations[location], 1, false, glm::value_ptr(matrix)); };
	void loadVector(const glm::vec3& vector, unsigned int location) { glUniform3f(locations[location], vector.x, vector.y, vector.z); };
	void loadVectorArray(glm::vec3* vectorArray, unsigned int arraySize, unsigned int location) { glUniform3fv(locations[location], arraySize, toArray(vectorArray, arraySize)); }
	void loadInt(int i, unsigned int location) { glUniform1i(locations[location], i); }
private:
	GLuint shaderProgram;
	GLuint shaders[2];
	GLuint* locations;

	string name;
	vector<string>* attributes;
};