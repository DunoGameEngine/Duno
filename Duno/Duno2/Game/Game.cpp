#include "Game.h"

using namespace Duno2;

void Game::onLoad() {

}

void Game::onUpdate() {
	
}

void Game::onClose() {

}

void Game::addLevel(Level level)
{

	m_levels.push_back(level);

}

void Duno2::Game::useLevel(std::string level)
{



}

void Game::addDisplay(Duno2::Graphics::Display display) {

	m_display = display;

}
