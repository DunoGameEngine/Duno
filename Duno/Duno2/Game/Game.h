#pragma once
#include <stdio.h>
#include <list>

#include "../Graphics/Display.h"
#include "Level.h"

namespace Duno2 {

	class Game {
		
	public:
		std::list<Level> levels = new std::list<Level>();

	};

}