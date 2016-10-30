#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include "DunoLightType.h"
using namespace std;

/* Store Final Light Data */
struct LightOut
{
	LightOut(unsigned int size) :
		m_point_positions(new glm::vec3[size]),
		m_point_colours(new glm::vec3[size]),
		m_size(size) {}
	
	/* Point Light Data */
	glm::vec3* m_point_positions;
	glm::vec3* m_point_colours;

	/* Number Of Lights */
	unsigned int m_size;

	~LightOut() { delete[] m_point_positions; delete[] m_point_colours; }
};

/* Manage Lights In A Scene */
class DunoLightManager
{
public:
	DunoLightManager() {}

	/* Add A New Light */
	void addLight(Light* light);

	/* Remove A Light */
	void removeLight(Light* light);

	/* Get Raw Light Data */
	LightOut getLightData(unsigned int size);

	/* Set Ambient Light Value */
	void setAmbientLight(glm::vec3 light) { m_ambient_light = light; }

	/* Return Ambient Light Value */
	glm::vec3 getAmbientLight() { return m_ambient_light; }
private:
	/* Get Lights To Render */
	Light** getLights(unsigned int max);

	/* Delete Lights */
	void deleteLights(Light** lights, unsigned int size);

	/* All Lights In World */
	vector<Light*> m_lights;

	/* The World's Ambient Light */
	glm::vec3 m_ambient_light;
};