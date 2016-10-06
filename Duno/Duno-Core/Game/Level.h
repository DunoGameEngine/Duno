#pragma once
#include <list>

#include "../Entities/DunoGameObject.h"

namespace Duno {

	class Level {

	private:

		//Name for the level (makes developing the game itself easier)
		std::string m_levelName;

		//List of entities 
		std::list<DunoGameObject> m_entities = std::list<DunoGameObject>();

		static std::string m_currentLevel;

	public:

		//Call when the Level starts
		void OnLoadLevel();

		//Call each frame
		void OnUpdateLevel();

		//Call when level about to close
		void OnCloseLevel();

		std::string getCurrentLevel() { return m_currentLevel; }
		void setCurrentLevel(std::string newLevel);


	};


}