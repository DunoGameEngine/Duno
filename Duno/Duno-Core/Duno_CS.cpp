#include "Duno_CS.h"

using namespace Duno;

Game::Game()
{

	OnLoad();

	while (true)
	{
		OnUpdate();

		if (fps > 10) {
			OnRender();
		}
	}

}
