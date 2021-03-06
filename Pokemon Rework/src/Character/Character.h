#pragma once
#include "../Dialog/Dialog.h"
#include "../Core/Sprite.h"
#include "SDL.h"
#include "../Core/Collision.h"
#include "../Core/Vector2.h"
#include "NpcPattern.h"
#include "../Quest/Quest.h"

enum class WalkDirection { DOWN, UP, LEFT, RIGHT, NONE };
class Trainer;
class Character
{
public:
	virtual ~Character();

	void Animate(AnimationDirection dir, int tickTimes);

public:
	virtual void Update(float elapsedTime) = 0;

public:
	void UpdateCharacter(float elapsedTime);
	SDL_Rect& GetPosition() { return position; }
	SDL_Rect& GetInteractPoint() { return interactPoint; }
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
	WalkDirection GetWalkDirect() { return walkDir; }
	void SetDirection(AnimationDirection dir) { animDir = dir; }
	void SetWalkDirection(WalkDirection dir) { walkDir = dir; }
	void Move(NpcPattern moveVec);
	std::vector<NpcPattern> GetMovePattern() { return movePattern; }
	void AddToMovePattern(NpcPattern pattern);
	bool GetIsWalking() { return isWalking; }
	bool GetIsTrainer() { return isTrainer; }
	bool GetCanWalk() { return canWalk; }
	bool IsVisible() { return isVisible; }
	int GetTileX(int tileSize, int zoom) { return xPos / tileSize / zoom; }
	int GetTileY(int tileSize, int zoom) { return yPos / tileSize / zoom; }
	std::vector<Quest*> GetQuest() { return quests; }
	Quest* GetQuestByNumber(int num);

public:
	void SetSrcRect(int x, int y, int w, int h);
	void SetXPos(int value) { xPos = value; }
	void SetYPos(int value) { yPos = value; }
	void SetSpeed(int value) { speed = value; }
	void MoveXPos(int value) { xPos += value; }
	void MoveYPos(int value) { yPos += value; }
	void SetXYPosition(int x, int y) { xPos = x; yPos = y; }
	void SetIsWalking(bool value) { isWalking = value; }
	void SetCanWalk(bool value) { canWalk = value; }
	void SetCollisionPoint(int x, int y, int w, int h);
	void SetInteractPoint(int x, int y, int w, int h);
	void SetVisibility(bool value);

public:
	void AddDialog(std::string message);
	void ClearDialog();
	void ClearPath();
	void AddNewQuest(Quest* quest) { quests.push_back(quest); }
	bool MoveTowardsPlayer(Trainer* player, int tileSize, int zoom);

protected:
	int xPos = 0;
	int yPos = 0;
	int width = 0;
	int height = 0;
	int speed = 4;
	bool isWalking = false;
	std::string name;
	SDL_Rect position;
	SDL_Rect srcRect;
	SDL_Rect interactPoint;
	SDL_Rect collisionPoint;
	std::string texturePath;
	Sprite* sprite = nullptr;
	AnimationDirection animDir = AnimationDirection::DOWN;
	WalkDirection walkDir = WalkDirection::NONE;
	std::vector<NpcPattern> movePattern;
	Dialog dialog;
	bool canWalk = true;
	bool isTrainer = false;
	int deltaX = 0;
	int deltaY = 0;
	bool isVisible = true;
	std::vector<Quest*> quests;
};