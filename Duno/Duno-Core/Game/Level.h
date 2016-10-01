#pragma once
#include <list>

#include "../GameObject/DunoGameObject.h"

namespace Duno {

	class Level {

	private:
		std::list<DunoGameObject> entities = std::list<DunoGameObject>();

	};

}