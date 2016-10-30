#include "GUIFile.h"

GUIFile GUIFile::load(XMLFile file, PlainModel* model, GLMateral* mat)
{
	GUIFile guiFile(file);
	for (XML::Tag tag : file.getBody().subs)
	{
		if (tag.name == "pannel")
		{
			DunoGUIPannel* pannel = new DunoGUIPannel(model, mat);
			pannel->load(tag);
			guiFile.elements.push_back(pannel);
		}
	}
	return guiFile;
}

void GUIFile::render(GLRenderer* renderer)
{
	for (DunoGUIElement* element : elements)
		renderer->addModel(element);
}