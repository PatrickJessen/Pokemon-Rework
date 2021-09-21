#include "PlayerController.h"

PlayerController::PlayerController(Character* player, Map* map)
	: player(player), map(map)
{
}

PlayerController::~PlayerController()
{
	
}

void PlayerController::Update()
{
	if (Input::KeyState(Key::W))
	{
		player->GetCollisionPoint() = { player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 2 + 5, 10, 10 };
		if (!TileCollision())
		{
			dynamic_cast<Trainer*>(player)->WalkUp();
			player->Animate(AnimationDirection::UP, 4);
			lastDirection = (int)AnimationDirection::UP;
		}
	}
	else if (Input::KeyState(Key::S))
	{
		player->GetCollisionPoint() = { player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 2 + 35, 10, 10 };
		if (!TileCollision())
		{
			dynamic_cast<Trainer*>(player)->WalkDown();
			player->Animate(AnimationDirection::DOWN, 4);
			lastDirection = (int)AnimationDirection::DOWN;
		}
	}
	else if (Input::KeyState(Key::A))
	{
		player->GetCollisionPoint() = { player->GetXPos() + player->GetWidth() / 2 - 15, player->GetYPos() + player->GetHeight() / 2 + 10, 10, 10 };
		if (!TileCollision())
		{
			dynamic_cast<Trainer*>(player)->WalkLeft();
			player->Animate(AnimationDirection::LEFT, 4);
			lastDirection = (int)AnimationDirection::LEFT;
		}
	}
	else if (Input::KeyState(Key::D))
	{
		player->GetCollisionPoint() = { player->GetXPos() + player->GetWidth() / 2 + 10, player->GetYPos() + player->GetHeight() / 2 + 10, 10, 10 };
		if (!TileCollision())
		{
			dynamic_cast<Trainer*>(player)->WalkRight();
			player->Animate(AnimationDirection::RIGHT, 4);
			lastDirection = (int)AnimationDirection::RIGHT;
		}
	}
	else
	{
		player->Animate((AnimationDirection)lastDirection, 1);
	}
	player->SetDirection((AnimationDirection)lastDirection);
	Interact();
}

bool PlayerController::TileCollision()
{
	if (map->GetTiles()[player->GetCollisionPoint().y / map->GetTileSize() / map->GetCamera()->GetZoom()][player->GetCollisionPoint().x / map->GetTileSize() / map->GetCamera()->GetZoom()].type == TileType::Collision)
		return true;
	return false;
}

void PlayerController::Interact()
{
	for (int i = 0; i < map->GetNpcs().size(); i++)
		if (Collision::AABB(player->GetCollisionPoint(), map->GetNpcs()[i]->GetPosition()))
			if (Input::KeyPressed(Key::E) && !map->GetNpcs()[i]->GetIsWalking())
			{
				map->SetCollidedNpc(map->GetNpcs()[i]);
				DialogManager::GetInstance()->SetIsActive(true);
				/*if (player->GetYPos() < map->GetCollidedNpc()->GetYPos())
				{
					map->GetCollidedNpc()->Animate(AnimationDirection::UP, 1);
					return;
				}
				if (player->GetXPos() < map->GetCollidedNpc()->GetXPos())
				{
					map->GetCollidedNpc()->Animate(AnimationDirection::LEFT, 1);
					return;
				}
				if (player->GetYPos() > map->GetCollidedNpc()->GetYPos())
				{
					map->GetCollidedNpc()->Animate(AnimationDirection::DOWN, 1);
					return;
				}
				if (player->GetXPos() > map->GetCollidedNpc()->GetXPos())
				{
					map->GetCollidedNpc()->Animate(AnimationDirection::RIGHT, 1);
					return;
				}*/
			}
}
