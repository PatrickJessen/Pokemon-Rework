#include "Window/Window.h"
#include "GameController.h"

int main()
{
	Window* window = new Window("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1700, 900, false);
	GameController* gController = new GameController();
	while (window->Running())
	{
		gController->Update();
		window->Update();
		window->HandleEvents();
	}

	window->Clean();
}