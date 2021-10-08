#include "Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include <chrono>

static SDL_Renderer* renderer;
static int mWidth;
static int mHeight;
static bool isRunning;
static float deltatime = 0;

static auto tp1 = std::chrono::system_clock::now();
static auto tp2 = std::chrono::system_clock::now();

Window::Window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	mWidth = width;
	mHeight = height;

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialized" << "\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << "\n";
		}
		SDL_GL_MakeCurrent(window, context);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created" << "\n";
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	Input.Update();
}
Window::~Window()
{

}

bool Window::Running()
{
	return isRunning;
}

int Window::GetWidth()
{
	return mWidth;
}

int Window::GetHeight()
{
	return mHeight;
}

void Window::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	Input.Update();
}


void Window::Update()
{
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = tp2 - tp1;
	float x = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
	tp1 = tp2;
	deltatime = elapsedTime.count() * 100;

	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 2;
	Uint32 spriteTick = (seconds) % 3;

	//deltatime = (float)spriteTick;

	Render();
	//HandleEvents();
	Clear();
}

void Window::Clear()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect = { 0, 0, mWidth, mHeight };

	SDL_RenderFillRect(renderer, &rect);
}

void Window::Render()
{
	SDL_RenderPresent(renderer);
}

void Window::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << "\n";
}

SDL_Renderer* Window::GetRender()
{
	return renderer;
}

float Window::GetDeltatime()
{
	return deltatime;
}
