#pragma once
#include "../GLTexture.h"
#include "GLMaterial.h"

/* Most Basic Type, Only Defuse Texture */
class GLMaterialBasic : public GLMaterial
{
public:
	GLMaterialBasic(GLTexture* defuse, float emitted, float specular):
		m_defuse(defuse),
		m_emitted(emitted),
		m_specular(specular),
		GLMaterial() { m_type = DUNOMETRRIAL_BASIC; }

	/* Getters */
	GLTexture* getDeffuse()  { return m_defuse; }
	float getLightEmitted()  { return m_emitted; }
	float getSpecularLight() { return m_specular; }
private:
	/* Defuse Texture */
	GLTexture* m_defuse;

	/* Amount Of Light Emitted */
	float m_emitted;

	/* Amount Of Light Reflected As Specular */
	float m_specular;
};

/* Material With Normal Map */
class GLMaterialBumped : public GLMaterialBasic
{
public:
	GLMaterialBumped(GLTexture* defuse, GLTexture* normal_map, float emitted, float specular):
		m_normal_map(normal_map),
		GLMaterialBasic(defuse, emitted, specular) { m_type = DUNOMETRRIAL_BUMPED; }

	/* Getters */
	GLTexture* getNormalMap() { return m_normal_map; }
private:
	/* Normal Map */
	GLTexture* m_normal_map;
};

/* Material With All Effects */
class GLMaterialFull : public GLMaterialBumped
{
public:
	GLMaterialFull(GLTexture* defuse, GLTexture* normal_map, GLTexture* specular_map, float emitted, float specular):
		m_specular_map(specular_map),
		GLMaterialBumped(defuse, normal_map, emitted, specular) { m_type = DUNOMETRRIAL_FULL; }

	/* Getters */
	GLTexture* getSpecularMap() { return m_specular_map; }
private:
	/* Specular Map */
	GLTexture* m_specular_map;
};