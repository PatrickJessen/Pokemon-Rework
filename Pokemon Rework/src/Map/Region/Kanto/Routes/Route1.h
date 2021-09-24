#pragma once
#include "../../../Map.h"
#include "../../../../Interfaces/ISpawnPokemon.h"
#include "../Pallet Town/PalletTown.h"

class Route1 : public Map, public ISpawnPokemon
{
public:
	Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~Route1();

	virtual Map* LoadNewMap() override;
	virtual Pokemon* SpawnPokemon() override;

private:
	Map* pTown = nullptr;
	Pokemon* spawnedPoke = nullptr;
};