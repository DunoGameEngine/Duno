#pragma once
#include "XMLFile.h"
#include "../GameObject/GUI/DunoGUIBasic.h"
#include "../Graphics/renderEngine/GLRenderer.h"

namespace FileType
{
	class GUIFile : public File
	{
	public:
		GUIFile(File file) : File(file) {}
		static GUIFile load(XMLFile file, PlainModel* model, GLMateral* mat);
		
		void render(GLRenderer* renderer);
	private:
		vector<DunoGUIElement*> elements;
	};
}