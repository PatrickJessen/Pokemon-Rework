#pragma once
#include "../../../Map.h"
#include "../../../../Interfaces/ISpawnPokemon.h"
#include "../Pallet Town/PalletTown.h"

class Route1 : public Map, public ISpawnPokemon, public ICheckpoint
{
public:
	Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~Route1();

	virtual Map* LoadNewMap() override;
	virtual Pokemon* SpawnPokemon() override;
	virtual Map* SpawnAtCheckpoint() override;
	virtual void Update() override;

private:
	Map* pTown = nullptr;
	Pokemon* spawnedPoke = nullptr;
};