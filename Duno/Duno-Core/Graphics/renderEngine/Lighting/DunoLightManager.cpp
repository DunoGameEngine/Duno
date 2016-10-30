#include "DunoLightManager.h"
#include <iostream>
using namespace std;

/* Add A New Light */
void DunoLightManager::addLight(Light* light)
{
	m_lights.push_back(light);
}

/* Remove A Light */
void DunoLightManager::removeLight(Light* light)
{
	m_lights.erase(find(m_lights.begin(), m_lights.end(), light));
}

/* Get Raw Light Data */
LightOut DunoLightManager::getLightData(unsigned int size)
{
	Light** lights = getLights(size);
	LightOut out(size);
	
	for (unsigned int i = 0; i < size; i++)
	{
		/* Set data for each light */
		switch (lights[i]->m_type)
		{
		case DUNOLIGHT_POINT:
			PointLight* point = static_cast<PointLight*>(lights[i]);
			out.m_point_positions[i] = point->m_position;
			out.m_point_colours[i] = point->m_colour;
		}
	}

	deleteLights(lights, size);
	return out;
}

/* Get Lights To Render */
Light** DunoLightManager::getLights(unsigned int max)
{
	Light** lights = new Light*[max];
	/* If there are more or equal to the amount of lights requested, */
	/* then return the first ones in the list                        */
	if (m_lights.size() >= max)
	{
		for (unsigned int i = 0; i < m_lights.size(); i++)
		{
			lights[i] = m_lights[i];
		}
	}
	/* Otherwise fill the rest up with null lights */
	else
	{
		for (unsigned int i = 0; i < max; i++)
		{
			if (m_lights.size() > i)
			{
				lights[i] = m_lights[i];
			}
			else
			{
				lights[i] = new NullLight();
			}
		}
	}

	return lights;
}

/* Delete Lights */
void DunoLightManager::deleteLights(Light** lights, unsigned int size)
{
	/* Delete the array */
	delete[] lights;
}