#include "Game.h"

using namespace Duno2;

void Game::onLoadGame() {

	//Create game display
	m_display.createDisplay(
		m_display.getDisplayWidth(),
		m_display.getDisplayHeight(),
		m_display.getDisplayTitle());

}

void Game::onUpdateGame() {


	//Update game display
	m_display.updateDisplay();
}

void Game::onCloseGame() {


	//Close game display
	m_display.closeDisplay();
}

void Game::addLevel(Level level)
{
	//Add the level to the list of levels
	m_levels.push_back(level);

}

void Duno2::Game::useLevel(std::string level)
{



}

void Game::addDisplay(Duno2::Graphics::Display display) {

	//Assign the display to be used by game
	m_display = display;

}
