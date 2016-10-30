#pragma once
#include <glm\glm.hpp>

/* Duno Light Types */
#define DUNOLIGHT_NULL 0
#define DUNOLIGHT_POINT 1

/* Generic Light Object */
struct Light
{
	Light(unsigned int type) : m_type(type) {}
	unsigned int m_type;
};

/* Duno NULL Light (fills in gaps where there is no light) */
struct NullLight : public Light
{
	NullLight() : Light(DUNOLIGHT_NULL) {}
};
/* Duno Point Light */
struct PointLight : public Light
{
	PointLight(glm::vec3 position, glm::vec3 colour) :
		Light(DUNOLIGHT_POINT),
		m_position(position),
		m_colour(colour) {}

	/* Position Of Light In World Space */
	glm::vec3 m_position;
	/* Colour And Intensity Of Light */
	glm::vec3 m_colour;
};