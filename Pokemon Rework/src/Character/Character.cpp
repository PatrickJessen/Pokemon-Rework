#include "Character.h"

Character::~Character()
{
	delete sprite;
}

void Character::Animate(AnimationDirection dir, int tickTimes)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 150 - (speed * 3);
	Uint32 spriteTick = (seconds) % tickTimes;
	if (dir == AnimationDirection::UP)
		srcRect = { ((int)spriteTick % 4) * 62, 3 * 65, 62, 65 };
	else if (dir == AnimationDirection::DOWN)
		srcRect = { ((int)spriteTick % 4) * 62, 0, 62, 65 };
	else if (dir == AnimationDirection::LEFT)
		srcRect = { ((int)spriteTick % 4) * 62, 65, 62, 65 };
	else if (dir == AnimationDirection::RIGHT)
		srcRect = { ((int)spriteTick % 4) * 62, 2 * 65, 62, 65 };
}
void Character::Update()
{
	position = { xPos, yPos, width, height };
	collisionPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 10 };
}

void Character::SetSrcRect(int x, int y, int w, int h)
{
	srcRect = { x, y, w, h };
}
