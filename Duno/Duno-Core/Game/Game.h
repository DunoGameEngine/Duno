#pragma once
#include <list>
#include "../Graphics/Display.h"
#include "Level.h"

namespace Duno {

	class Game {

	private:
		Duno::Graphics::Display* m_display;


	public:
		Game();

		virtual void OnLoadGame()		= 0;
		virtual void OnUpdateGame()		= 0;
		virtual void OnRenderGame()		= 0;
		virtual void OnClosingGame()	= 0;
		virtual void OnClosedGame()		= 0;

	private:

		void OnLoad();
		void OnUpdate();
		void OnRender();
		void OnClosing();
		void OnClosed();

	};

}