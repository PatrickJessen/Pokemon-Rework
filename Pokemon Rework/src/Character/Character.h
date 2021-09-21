#pragma once
#include "../Dialog/Dialog.h"
#include "../Core/Sprite.h"
#include "SDL.h"
#include "../Core/Collision.h"
#include "../Core/Vector2.h"
#include "NpcPattern.h"

class Character
{
public:
	virtual ~Character();
	void Animate(AnimationDirection dir, int tickTimes);
public:
	virtual void Update() = 0;
public:
	void UpdateCharacter();
	SDL_Rect& GetPosition() { return position; }
	SDL_Rect& GetCollisionPoint() { return collisionPoint; }
	SDL_Rect& GetSrcRect() { return srcRect; }
	Sprite* GetSprite() { return sprite; }
	Dialog GetDialog() { return dialog; }
	int GetXPos() { return xPos; }
	int GetYPos() { return yPos; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetSpeed() { return speed; }
	std::string GetName() { return name; }
	AnimationDirection GetDirection() { return animDir; }
	void SetDirection(AnimationDirection dir) { animDir = dir; }
	void Move(NpcPattern moveVec);
	std::vector<NpcPattern> GetMovePattern() { return movePattern; }
	void AddToMovePattern(NpcPattern pattern);
	bool GetIsWalking() { return isWalking; }
	bool GetIsTrainer() { return isTrainer; }

public:
	void SetSrcRect(int x, int y, int w, int h);
	void SetXPos(int value) { xPos = value; }
	void SetYPos(int value) { yPos = value; }
	void SetXYPosition(int x, int y) { xPos = x; yPos = y; }
	void SetIsWalking(bool value) { isWalking = value; }
	void SetCanWalk(bool value) { canWalk = value; }
	Dialog dialog;

protected:
	int xPos = 0;
	int yPos = 0;
	int width = 0;
	int height = 0;
	int speed = 5;
	bool isWalking = false;
	std::string name;
	SDL_Rect position;
	SDL_Rect srcRect;
	SDL_Rect collisionPoint;
	std::string texturePath;
	Sprite* sprite = nullptr;
	AnimationDirection animDir;
	std::vector<NpcPattern> movePattern;
	bool canWalk = true;
	bool isTrainer = false;
};