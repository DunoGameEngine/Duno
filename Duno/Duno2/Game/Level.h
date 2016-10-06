#pragma once
#include "../Entities/Entity.h"

namespace Duno2 {

	class Level {

	private:
		//List of entities on this level
		std::list<Entities::Entity> entities = std::list<Entities::Entity>();

		//Name of the level (makes manipulating levels easier for dev)
		std::string m_levelName;


	};

}