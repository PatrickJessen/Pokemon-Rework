#include "../Core/Vector2.h"
#include "Map.h"
#include "Region/Kanto/Pallet Town/PalletTown.h"

class Checkpoint
{
public:
	void InitCheckpoints(Character* player)
	{
		this->player = player;
		Map* pTown = new PalletTown(player, 31, 31, 32, 1, 2);
		checkpoints.emplace(pTown, std::vector<Vector2>{Vector2(5, 11)});
	}

	void SetCurrentCheckpoint(Camera* cam)
	{
		for (auto& x : checkpoints)
		{
			for (int i = 0; i < x.second.size(); i++)
			{
				//std::cout << x.second[i].x << ", " << x.second[i].y << "\n"
				//std::cout << player->GetInteractPoint().x / x.first->GetTileSize() / x.first->GetCamera()->GetZoom() << ", " << player->GetInteractPoint().y / x.first->GetTileSize() / x.first->GetCamera()->GetZoom() << ", " << x.second[i].x << ", " << x.second[i].y << "\n";
				if (x.second[i].x == player->GetInteractPoint().x / x.first->GetTileSize() / cam->GetZoom() && x.second[i].y == player->GetInteractPoint().y / x.first->GetTileSize() / cam->GetZoom())
				{
					currentCheckpoint = x.first;
					position = &x.second[i];
					//std::cout << "checkpoint reached\n";
				}
			}
		}
	}

	Map* GetCurrentCheckpoint()
	{
		return currentCheckpoint;
	}

	Vector2* GetPosition() { return position; }

private:
	std::map<Map*, std::vector<Vector2>> checkpoints;
	Map* currentCheckpoint = nullptr;
	Vector2* position;
	Character* player = nullptr;
};