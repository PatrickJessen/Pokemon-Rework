#include "Character.h"

Character::~Character()
{
	delete sprite;
}

void Character::Animate(AnimationDirection dir, int tickTimes)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 1000;
	Uint32 spriteTick = (ticks / 100) % tickTimes;

	if (dir == AnimationDirection::UP)
	{
		srcRect = { (int)spriteTick * 62, 3 * 65, 62, 65 };
	}		
	else if (dir == AnimationDirection::DOWN)
	{
		srcRect = { (int)spriteTick * 62, 0, 62, 65 };
	}
	else if (dir == AnimationDirection::LEFT)
	{
		srcRect = { (int)spriteTick * 62, 65, 62, 65 };
	}
	else if (dir == AnimationDirection::RIGHT)
	{
		srcRect = { (int)spriteTick * 62, 2 * 65, 62, 65 };
	}
	//SDL_Delay(20);
	animDir = dir;
}


void Character::UpdateCharacter(float elapsedTime)
{
	Update(elapsedTime);
	position = { xPos, yPos, width, height };
	collisionPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 10 };
	SDL_RenderDrawRect(Window::GetRender(), &collisionPoint);
	switch (animDir)
	{
	case AnimationDirection::UP:
		interactPoint = { xPos + width / 2, yPos, 10, 30 };
		break;
	case AnimationDirection::DOWN:
		interactPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 30 };
		break;
	case AnimationDirection::LEFT:
		interactPoint = { xPos, yPos + height / 2 + 5, 30, 10 };
		break;
	case AnimationDirection::RIGHT:
		interactPoint = { xPos + width / 2, yPos + height / 2 + 5, 30, 10 };
		break;
	default:
		break;
	}
}

void Character::Move(NpcPattern moveVec)
{
	if (moveVec.direction == AnimationDirection::RIGHT)
		xPos += moveVec.vector2.x / 10;
	if (moveVec.direction == AnimationDirection::LEFT)
		xPos -= moveVec.vector2.x / 5;
	if (moveVec.direction == AnimationDirection::UP)
		yPos += moveVec.vector2.y - 10;
	if (moveVec.direction == AnimationDirection::DOWN)
		yPos += moveVec.vector2.y / 10;
	//if (xPos != xPos + moveVec.vector2.x)
		//xPos += speed;
	//else if (yPos != yPos + moveVec.vector2.y)
		//yPos -= speed;
}

void Character::AddToMovePattern(NpcPattern pattern)
{
	movePattern.push_back(pattern);
}

void Character::SetSrcRect(int x, int y, int w, int h)
{
	srcRect = { x, y, w, h };
}

void Character::SetCollisionPoint(int x, int y, int w, int h)
{
	collisionPoint.x = x;
	collisionPoint.y = y;
	collisionPoint.w = w;
	collisionPoint.h = h;
}
