#pragma once
#include "../OpenGL/GL.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
using namespace std;

/* Represents an handles a OpenGL shader */
class GLShader
{
public:
	GLShader(string name) : m_name(name), m_attributes(new vector<string>()) {};
	
	/* Start Shader Compile Time */
	void compile();
	
	/* Allocates an amount of space to store the uniform locations */
	void allocateLocations(unsigned int size) { m_locations = new GLuint[size]; }

	/* Allocates Space For Subroutines */
	void allocateSubroutines(unsigned int size) { m_subroutines = new GLuint[size]; }

	/* Expands the current uniform locations storage space */
	void expandeLoactions(unsigned int from, unsigned int to) { GLuint* loc = new GLuint[to]; for (unsigned int i = 0; i < from; i++) loc[i] = m_locations[i]; delete m_locations; m_locations = loc; }
	
	/* Assigns a location */
	void setLocation(unsigned int location, string uniform) { m_locations[location] = glGetUniformLocation(m_shader_program, uniform.c_str()); };
	
	/* Assigns Subroutine */
	void setSubroutine(unsigned int location, GLenum shader, string name) { m_subroutines[location] = glGetSubroutineIndex(m_shader_program, shader, name.c_str()); }

	/* Adds an attribute before compile */
	void addAtribute(string attribute);
	
	/* Binds this shader */
	void bind() { glUseProgram(m_shader_program); }
	
	/* Unbinds the current shader */
	void unbind() { glUseProgram(0); }

	/* Converts a vector array to a GLFloat array */
	GLfloat* toArray(glm::vec3* vectorArray, unsigned int arraySize) { GLfloat* fa = new GLfloat[arraySize * 3]; for (unsigned int i = 0; i < arraySize; i++) { fa[i * 3] = vectorArray[i].x; fa[(i * 3) + 1] = vectorArray[i].y; fa[(i * 3) + 2] = vectorArray[i].z; } return fa; }

	/* Loads a matrix to a uniform */
	void loadMatrix(const glm::mat4& matrix, unsigned int location) { glUniformMatrix4fv(m_locations[location], 1, false, glm::value_ptr(matrix)); };
	void loadVector(const glm::vec3& vector, unsigned int location) { glUniform3f(m_locations[location], vector.x, vector.y, vector.z); };
	void loadVectorArray(glm::vec3* vectorArray, unsigned int arraySize, unsigned int location)
	{ 
		GLfloat* a = toArray(vectorArray, arraySize);
		glUniform3fv(m_locations[location], arraySize, a);
		delete[] a;
	}
	void loadInt(int i, unsigned int location) { glUniform1i(m_locations[location], i); }
	void loadFloat(float f, unsigned int location) { glUniform1f(m_locations[location], f); }

	/* Select Subroutine */
	void loadSubroutine(GLenum shader, GLuint subroutine) { glUniformSubroutinesuiv(shader, 1, &m_subroutines[subroutine]); }

	~GLShader();
private:
	GLuint m_shader_program;
	GLuint m_shaders[2];
	GLuint* m_locations;
	GLuint* m_subroutines;

	string m_name;
	vector<string>* m_attributes;
};