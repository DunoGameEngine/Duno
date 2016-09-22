#pragma once

namespace Duno {

	class Game {

	private:

		int fps;

	public:

		Game();

		//override those in the C# code
		virtual void OnLoad() {};
		virtual void OnUpdate() {};
		virtual void OnRender() {};
		virtual void OnClose() {};


	};
}