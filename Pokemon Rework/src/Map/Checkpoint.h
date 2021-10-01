#include "../Core/Vector2.h"
#include "Map.h"
#include "Region/Kanto/Pallet Town/PalletTown.h"

class TestClass
{
public:
	TestClass(Map* map, Vector2 vec2)
		: map(map), vec2(vec2) {}

	Map* map;
	Vector2 vec2;
};

class Checkpoint
{
public:
	Checkpoint() = default;
	void InitCheckpoints(Character* player)
	{
		this->player = player;
		pTown = new PalletTown(player, 31, 31, 32, 1, 2);
		//checkpoints.emplace(pTown, Vector2(5, 11));
		testing.push_back(new TestClass(pTown, Vector2(5, 11)));
		testmap = pTown;
		currentCheckpoint = new Route1(player, 51, 51, 32, 2, 2);
	}

	void SetCurrentCheckpoint(Camera* cam)
	{
		for (int i = 0; i < testing.size(); i++)
		{
			if (testing[i]->vec2.x == player->GetInteractPoint().x / testing[i]->map->GetTileSize() / cam->GetZoom() && testing[i]->vec2.y == player->GetInteractPoint().y / testing[i]->map->GetTileSize() / cam->GetZoom())
			{
				//Map* pTown1 = PalletTown(player, 31, 31, 32, 1, 2);
				std::memcpy(currentCheckpoint, testing[i]->map, sizeof(testing[i]->map));
				
				position = &testing[i]->vec2;
				std::cout << "checkpoint reached\n";
			}
		}
		//for (auto& x : checkpoints)
		//{
		//	//std::cout << x.second[i].x << ", " << x.second[i].y << "\n"
		//	//std::cout << player->GetInteractPoint().x / x.first->GetTileSize() / x.first->GetCamera()->GetZoom() << ", " << player->GetInteractPoint().y / x.first->GetTileSize() / x.first->GetCamera()->GetZoom() << ", " << x.second[i].x << ", " << x.second[i].y << "\n";
		//	if (x.second.x == player->GetInteractPoint().x / x.first->GetTileSize() / cam->GetZoom() && x.second.y == player->GetInteractPoint().y / x.first->GetTileSize() / cam->GetZoom())
		//	{
		//		currentCheckpoint = x.first;
		//		position = &x.second;
		//		//std::cout << "checkpoint reached\n";
		//	}
		//}
	}

	void NullifyCheckpoint() 
	{ 
		delete currentCheckpoint;
	}

	const Map* GetCurrentCheckpoint()
	{
		return currentCheckpoint;
	}

	Vector2* GetPosition() { return position; }

	Map* currentCheckpoint = nullptr;
private:
	Map* pTown;
	std::map<Map, Vector2> checkpoints;
	std::vector<TestClass*> testing;
	Map* testmap;
	Vector2* position;
	Character* player = nullptr;
};