#pragma once
#include <list>

#include "../GameObject/DunoGameObject.h"

namespace Duno {

	class Level {

	private:
		char* m_levelName;
		std::list<DunoGameObject> m_entities = std::list<DunoGameObject>();

	};

}