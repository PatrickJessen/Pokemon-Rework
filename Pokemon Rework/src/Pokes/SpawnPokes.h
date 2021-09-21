#pragma once
#include "Pokemon.h"

class SpawnPokes
{
public:
	SpawnPokes(Pokemon* pokemon, int spawnRate, int catchRate)
		: Pokemon(pokemon), SpawnRate(spawnRate), CatchRate(catchRate)
	{}

	Pokemon* Pokemon;
	int SpawnRate;
	int CatchRate;
};