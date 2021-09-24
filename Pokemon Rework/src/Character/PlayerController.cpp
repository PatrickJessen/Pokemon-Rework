#include "PlayerController.h"
#include "../Interfaces/ISpawnPokemon.h"
#include "../Battle/BattlePokemon.h"

PlayerController::PlayerController(Character* player, Map* map)
	: player(player), map(map)
{
}

PlayerController::~PlayerController()
{
	
}

void PlayerController::Update(float elapsedTime)
{
	if (timer == 0 && player->GetCanWalk())
	{
		if (Input::KeyState(Key::W))
		{
			player->SetWalkDirection(WalkDirection::UP);
		}
		else if (Input::KeyState(Key::S))
		{
			player->SetWalkDirection(WalkDirection::DOWN);
		}
		else if (Input::KeyState(Key::A))
		{
			player->SetWalkDirection(WalkDirection::LEFT);
		}
		else if (Input::KeyState(Key::D))
		{
			player->SetWalkDirection(WalkDirection::RIGHT);
		}
		else
		{
			player->SetIsWalking(false);
			//player->Animate((AnimationDirection)lastDirection, 1);
		}
	}
	Walk();
	Interact();
}

void PlayerController::Walk()
{
	if (player->GetWalkDirect() == WalkDirection::UP)
	{
		timer += player->GetSpeed();
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 4 - 10, 10, 10);
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision(TileType::Collision) && !TileCollision(TileType::NPC))
		{
			//if (!Collision::XYInRect(player->GetCollisionPoint(), map->GetTiles()[(player->GetCollisionPoint().y) / map->GetTileSize() / map->GetCamera()->GetZoom()][(player->GetCollisionPoint().x) / map->GetTileSize() / map->GetCamera()->GetZoom()].textureX, map->GetTiles()[(player->GetCollisionPoint().y) / map->GetTileSize() / map->GetCamera()->GetZoom()][(player->GetCollisionPoint().x) / map->GetTileSize() / map->GetCamera()->GetZoom()].textureY))
			player->MoveYPos(-player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::UP, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::UP;
			player->SetWalkDirection(WalkDirection::NONE);
			Spawn();
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::DOWN)
	{
		timer += player->GetSpeed();
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() / 2 + 35, 10, 10);
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision(TileType::Collision) && !TileCollision(TileType::NPC))
		{
			player->MoveYPos(player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::DOWN, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::DOWN;
			player->SetWalkDirection(WalkDirection::NONE);
			Spawn();
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::LEFT)
	{
		timer += player->GetSpeed();
		player->SetCollisionPoint(player->GetXPos() - player->GetWidth() / 16 + 10, player->GetYPos() + player->GetHeight() / 2 + 10, 10, 10);
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision(TileType::Collision) && !TileCollision(TileType::NPC))
		{
			player->MoveXPos(-player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::LEFT, 4);
		}
		else
		{
			timer = 0;
			lastDirection = (int)AnimationDirection::LEFT;
			player->SetWalkDirection(WalkDirection::NONE);
			Spawn();
		}
	}
	else if (player->GetWalkDirect() == WalkDirection::RIGHT)
	{
		timer += player->GetSpeed();
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth(), player->GetYPos() + player->GetHeight() / 2 + 10, player->GetWidth() / 2, 10);
		if (timer <= map->GetTileSize() * map->GetCamera()->GetZoom() && !TileCollision(TileType::Collision) && !TileCollision(TileType::NPC))
		{
			player->MoveXPos(player->GetSpeed());
			player->Animate((AnimationDirection)WalkDirection::RIGHT, 4);
		}
		else
		{

			timer = 0;
			lastDirection = (int)AnimationDirection::RIGHT;
			player->SetWalkDirection(WalkDirection::NONE);
			Spawn();
		}
	}
	else
	{
		player->Animate((AnimationDirection)lastDirection, 1);
		player->SetCollisionPoint(player->GetXPos() + player->GetWidth() / 4, player->GetYPos() + player->GetHeight() / 2 + 5, player->GetWidth() / 2, 10);
	}
}

bool PlayerController::TileCollision(TileType type)
{
	/*if (map->GetTiles()[player->GetCollisionPoint().y / map->GetTileSize() / map->GetCamera()->GetZoom()][player->GetCollisionPoint().x / map->GetTileSize() / map->GetCamera()->GetZoom()].type == TileType::Collision)
		return true;*/
	//std::cout << player->GetCollisionPoint().x / map->GetTileSize() / map->GetCamera()->GetZoom() << ", " << player->GetCollisionPoint().y / map->GetTileSize() / map->GetCamera()->GetZoom() << "\n";
	if (map->GetTiles()[(player->GetCollisionPoint().y) / map->GetTileSize() / map->GetCamera()->GetZoom()][(player->GetCollisionPoint().x) / map->GetTileSize() / map->GetCamera()->GetZoom()].type == type)
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
				if (player->GetDirection() == AnimationDirection::UP)
					map->GetCollidedNpc()->Animate(AnimationDirection::DOWN, 1);
				else if (player->GetDirection() == AnimationDirection::DOWN)
					map->GetCollidedNpc()->Animate(AnimationDirection::UP, 1);
				else if (player->GetDirection() == AnimationDirection::LEFT)
					map->GetCollidedNpc()->Animate(AnimationDirection::RIGHT, 1);
				else if (player->GetDirection() == AnimationDirection::RIGHT)
					map->GetCollidedNpc()->Animate(AnimationDirection::LEFT, 1);
				break;
			}

}

bool PlayerController::IRanIntoPokemon()
{
	if (Random::InRange(0, 200) < 20)
		return true;
	return false;
}

void PlayerController::Spawn()
{
	if (TileCollision(TileType::Grass))
	{
		if (IRanIntoPokemon())
		{
			battle = new BattlePokemon(player, dynamic_cast<ISpawnPokemon*>(map)->SpawnPokemon());
			dynamic_cast<Trainer*>(player)->SetIsInPokemonBattle(true);
		}
	}
}
