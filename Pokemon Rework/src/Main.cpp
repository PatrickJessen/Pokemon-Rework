#include "Window/Window.h"
#include "GameController.h"

int main()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Window* window = new Window("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1700, 900, false);
	GameController* gController = new GameController();
	while (window->Running())
	{
		/*frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}*/
		gController->Update(0);
		window->Update();
		window->HandleEvents();
		SDL_Delay(1);
	}
	window->Clean();
}