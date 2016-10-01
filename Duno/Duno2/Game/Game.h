#pragma once
#include <stdio.h>
#include <list>

#include "../Graphics/Display.h"
#include "Level.h"

namespace Duno2 {

	class Game {
	private:
		//List of all levels used in the game (unloaded to save memory)
		std::list<Level> m_levels = std::list<Level>();

		//The display
		Duno2::Graphics::Display m_display;

	public:
		
		//Execute before the main game loop
		void onLoad();

		//Execute every frame
		void onUpdate();

		//Execute when the game is about to close
		void onClose();

		//Add a level to the game (make sure the level exists)
		void addLevel(Level level);

		//Allow dynamic change of the levels on command
		void useLevel(std::string level);

		//Assign the display to the game
		void addDisplay(Duno2::Graphics::Display);

	};

}