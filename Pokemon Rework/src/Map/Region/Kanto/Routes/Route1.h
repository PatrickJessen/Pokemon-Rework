#pragma once
#include "../../../Map.h"
#include "../../../ISpawnPokemon.h"

class Route1 : public Map
{
public:
	Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~Route1();

	virtual Map* LoadNewMap() override;
};