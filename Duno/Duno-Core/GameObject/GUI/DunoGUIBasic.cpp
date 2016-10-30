#include "DunoGUIBasic.h"
#include "../Graphics/Display/DunoDisplayInfo.h"

#define EOS(str) str[str.length()-1]

inline glm::vec3 toGUISpace(glm::vec2 vec)
{
	glm::vec3 out;
	out.x = ((vec.x / DunoDisplayInfo::getWidth()) - 0.5F) * 2;
	out.y = ((vec.y / DunoDisplayInfo::getHeight()) - 0.5F) * 2;
	return out;
}
void DunoGUIPannel::setPhysical(string constent, float& value, float* scaler)
{
	if (constent == "NULL") return;

	if (EOS(constent) == '%') value = stof(constent);
	else toUpdate.push_back(new Updater(stof(constent), value, scaler));
}

void DunoGUIPannel::load(XML::Tag tag)
{
	float w = 0;
	float h = 0;
	this->width = &w;
	this->height = &h;

	setPhysical(tag["width"], scale.x, width);
	setPhysical(tag["height"], scale.y, height);
}

void DunoGUIPannel::update()
{
	*width = DunoDisplayInfo::getWidth();
	*height = DunoDisplayInfo::getHeight();
	for (Updater* update : toUpdate)
		update->update();
}