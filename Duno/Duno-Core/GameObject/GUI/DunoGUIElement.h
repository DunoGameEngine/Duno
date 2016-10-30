#pragma once
#include "../DunoGameObject.h"
#include "../Assets/FileLoader/XMLFile.h"
using namespace FileType;

class DunoGUIElement : public DunoGameObject
{
public:
	DunoGUIElement(PlainModel* model, GLMateral* mat, glm::vec2 position, glm::vec2 scale) :
		DunoGameObject(model, mat, glm::vec3(position, 0.0F), glm::vec3(), glm::vec3(scale, 1.0F)) {}
	virtual void load(XML::Tag tag) = 0;
	virtual void update() = 0;
};
