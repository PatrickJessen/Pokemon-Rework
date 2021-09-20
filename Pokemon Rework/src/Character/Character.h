#pragma once
#include "../Dialog/Dialog.h"
#include "../Core/Sprite.h"
#include "SDL.h"

enum class AnimationDirection
{
	UP, DOWN, LEFT, RIGHT
};

class Character
{
public:
	virtual ~Character();
	void Animate(AnimationDirection dir, int tickTimes);
public:
	void Update();
public:
	SDL_Rect& GetPosition() { return position; }
	SDL_Rect& GetCollisionPoint() { return collisionPoint; }
	SDL_Rect& GetSrcRect() { return srcRect; }
	Sprite* GetSprite() { return sprite; }
	int GetXPos() { return xPos; }
	int GetYPos() { return yPos; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetSpeed() { return speed; }

public:
	void SetSrcRect(int x, int y, int w, int h);
	void SetXPos(int value) { xPos = value; }
	void SetYPos(int value) { yPos = value; }
	void SetXYPosition(int x, int y) { xPos = x; yPos = y; }

protected:
	int xPos = 0;
	int yPos = 0;
	int width = 0;
	int height = 0;
	int speed = 5;
	std::string name;
	SDL_Rect position;
	SDL_Rect srcRect;
	SDL_Rect collisionPoint;
	std::string texturePath;
	Sprite* sprite = nullptr;
	Dialog dialog;
};