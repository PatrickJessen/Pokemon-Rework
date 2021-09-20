#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "../Core/Input.h"
#include <thread>

class Window
{
public:
	Window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Window();

	static void HandleEvents();
	static void Update();
	static void Clear();
	static void Render();
	void Clean();
	static SDL_Renderer* GetRender();
	static float GetDeltatime();

	bool Running();

public:
	static int GetWidth();
	static int GetHeight();

public:
	SDL_Rect rect;

private:
	SDL_Window* window;
	SDL_GLContext context;
};

