#include "Character.h"
#include "Trainer.h"

Character::~Character()
{
	delete sprite;
	for (int i = 0; i < quests.size(); i++)
		delete quests[i];
	quests.clear();
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
		srcRect = { (int)spriteTick * 62, 65, 62, 63 };
	}
	else if (dir == AnimationDirection::RIGHT)
	{
		srcRect = { (int)spriteTick * 62, 2 * 65, 62, 63 };
	}
	//SDL_Delay(20);
	animDir = dir;
}

void Character::UpdateCharacter(float elapsedTime)
{
	Update(elapsedTime);
	position = { xPos, yPos, width, height };
	collisionPoint = { xPos + width / 4, yPos + height / 2 + 5, width / 2, 10 };
	//SDL_RenderDrawRect(Window::GetRender(), &collisionPoint);
	switch (animDir)
	{
	case AnimationDirection::UP:
		interactPoint = { xPos + width / 2, yPos, 10, 30 };
		break;
	case AnimationDirection::DOWN:
		interactPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 30 };
		break;
	case AnimationDirection::LEFT:
		interactPoint = { xPos, yPos + height / 2 + 4, 30, 10 };
		break;
	case AnimationDirection::RIGHT:
		interactPoint = { xPos + width, yPos + height / 2 + 4, 30, 10 };
		break;
	default:
		break;
	}

	if (!isVisible)
	{
		SDL_SetTextureBlendMode(sprite->tex, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(sprite->tex, 0);
	}
	else
		SDL_SetTextureAlphaMod(sprite->tex, 255);

}

void Character::Move(NpcPattern moveVec)
{
	if (moveVec.direction == AnimationDirection::RIGHT)
	{
		SetCollisionPoint(GetXPos() + GetWidth() - 15, GetYPos() + GetHeight() / 2 + 10, GetWidth() / 2, 10);
		xPos += speed; //moveVec.vector2.x / 10;
	}
	if (moveVec.direction == AnimationDirection::LEFT)
	{
		SetCollisionPoint(GetXPos() - GetWidth() / 16 + 10, GetYPos() + GetHeight() / 2 + 10, 10, 10);
		xPos -= speed;// moveVec.vector2.x / 5;
	}
	if (moveVec.direction == AnimationDirection::UP)
	{
		SetCollisionPoint(GetXPos() + GetWidth() / 2, GetYPos() + GetHeight() / 4 - 10, 10, 10);
		yPos -= speed;// moveVec.vector2.y - 10;
	}
	if (moveVec.direction == AnimationDirection::DOWN)
	{
		SetCollisionPoint(GetXPos() + GetWidth() / 2, GetYPos() + GetHeight() / 2 + 35, 10, 10);
		yPos += speed;// moveVec.vector2.y / 10;
	}
	//if (xPos != xPos + moveVec.vector2.x)
		//xPos += speed;
	//else if (yPos != yPos + moveVec.vector2.y)
		//yPos -= speed;
}

void Character::AddToMovePattern(NpcPattern pattern)
{
	movePattern.push_back(pattern);
}

Quest* Character::GetQuestByNumber(int num)
{
	for (int i = 0; i < quests.size(); i++)
		if (quests[i]->GetNumber() == num)
			return quests[i];

	return nullptr;
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

void Character::SetInteractPoint(int x, int y, int w, int h)
{
	interactPoint = { x, y, w, h };
}

void Character::SetVisibility(bool value)
{
	isVisible = value;
}

void Character::AddDialog(std::string message)
{
	dialog.Lines.push_back(message);
}

void Character::ClearDialog()
{
	dialog.Lines.clear();
}

void Character::ClearPath()
{
	movePattern.clear();
}

bool Character::MoveTowardsPlayer(Trainer* player, int tileSize, int zoom)
{
	/*if (GetTileX(tileSize, zoom) - 1 < player->GetTileX(tileSize, zoom))
		xPos += speed;*/
	if (GetTileY(tileSize, zoom) - 1 > player->GetTileY(tileSize, zoom))
	{
		isWalking = true;
		Animate(AnimationDirection::UP, 4);
		yPos -= speed;
	}
	else if (GetTileX(tileSize, zoom) > player->GetTileX(tileSize, zoom))
	{
		isWalking = true;
		Animate(AnimationDirection::LEFT, 4);
		xPos -= speed;
	}
	//else if (GetTileY(tileSize, zoom) + 1 < player->GetTileY(tileSize, zoom))
	//	yPos += speed;
	else
	{
		isWalking = false;
		Animate(player->GetDirection(), 1);
		return true;
	}
	return false;
}
