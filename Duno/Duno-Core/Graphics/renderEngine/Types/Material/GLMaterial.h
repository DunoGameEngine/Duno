#pragma once

#define DUNOMETRRIAL_BASIC  0
#define DUNOMETRRIAL_BUMPED 1
#define DUNOMETRRIAL_FULL   2

/* Stores the collection of textures that make up the objects material */
class GLMaterial
{
public:
	/* Creates a mat with a bump map */
	GLMaterial() {}

	unsigned int getType() { return m_type; }
protected:
	/* Material Type */
	unsigned int m_type;
};