#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
using namespace std;

struct Light
{
	Light(string type) : type(type) {}
	string type;
};
struct DirectionalLight : public Light
{
	DirectionalLight(glm::vec3 dir, glm::vec3 colour) :
		Light("Directional"),
		dir(dir),
		colour(colour) {}
	glm::vec3 dir;
	glm::vec3 colour;
};

class DunoLightManager
{
public:

private:
	vector<Light*> light;
};