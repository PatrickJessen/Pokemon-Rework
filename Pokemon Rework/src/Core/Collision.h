#pragma once
#include "SDL.h"


class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool XYInRect(const SDL_Rect& rect, int x, int y);
};