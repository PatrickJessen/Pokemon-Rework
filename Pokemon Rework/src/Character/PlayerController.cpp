#include "PlayerController.h"

PlayerController::PlayerController(Character* player, Map* map)
	: player(player), map(map)
{
}

PlayerController::~PlayerController()
{
	
}

void PlayerController::Update(float elapsedTime)
{

	if (Input::KeyState(Key::W))
	{
		player->SetWalkDirection(WalkDirection::UP);
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 2 + 5, 10, 10);
	}
	else if (Input::KeyState(Key::S))
	{
		player->SetWalkDirection(WalkDirection::DOWN);
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 2 + 35, 10, 10 );
	}
	else if (Input::KeyState(Key::A))
	{
		player->SetWalkDirection(WalkDirection::LEFT);
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2 - 15, player->GetYPos() + player->GetHeight() / 2 + 10, 10, 10);
	}
	else if (Input::KeyState(Key::D))
	{
		player->SetWalkDirection(WalkDirection::RIGHT);
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2 + 10, player->GetYPos() + player->GetHeight() / 2 + 10, 10, 10 );
	}
	else
	{
		player->SetIsWalking(false);
		//player->Animate((AnimationDirection)lastDirection, 1);
	}
	Walk();
	Interact();
}

void PlayerController::Walk()
{
	if (player->GetWalkDirect() == WalkDirection::UP)
	{
		timer += player->GetSpeed();
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision() && !NPCCollision())
		{
			player->MoveYPos(-player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::UP, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::UP;
			player->SetWalkDirection(WalkDirection::NONE);
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::DOWN)
	{
		timer += player->GetSpeed();
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision() && !NPCCollision())
		{
			player->MoveYPos(player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::DOWN, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::DOWN;
			player->SetWalkDirection(WalkDirection::NONE);
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::LEFT)
	{
		timer += player->GetSpeed();
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision() && !NPCCollision())
		{
			player->MoveXPos(-player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::LEFT, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::LEFT;
			player->SetWalkDirection(WalkDirection::NONE);
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::RIGHT)
	{
		timer += player->GetSpeed();
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision() && !NPCCollision())
		{
			player->MoveXPos(player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::RIGHT, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::RIGHT;
			player->SetWalkDirection(WalkDirection::NONE);
		}
	}
	else
		player->Animate((AnimationDirection)lastDirection, 1);
}

bool PlayerController::TileCollision()
{
	if (map->GetTiles()[player->GetCollisionPoint().y / map->GetTileSize() / map->GetCamera()->GetZoom()][player->GetCollisionPoint().x / map->GetTileSize() / map->GetCamera()->GetZoom()].type == TileType::Collision)
		return true;
	return false;
}

bool PlayerController::NPCCollision()
{
	if (map->GetTiles()[player->GetCollisionPoint().y / map->GetTileSize() / map->GetCamera()->GetZoom()][player->GetCollisionPoint().x / map->GetTileSize() / map->GetCamera()->GetZoom()].type == TileType::NPC)
		return true;
	return false;
}

void PlayerController::Interact()
{
	for (int i = 0; i < map->GetNpcs().size(); i++)
		if (Collision::AABB(player->GetInteractPoint(), map->GetNpcs()[i]->GetPosition()))
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
