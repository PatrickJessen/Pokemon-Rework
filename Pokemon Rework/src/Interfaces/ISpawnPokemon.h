#pragma once
#include "../Pokes/SpawnPokes.h"
#include <vector>

//Interface to use on areas that contains pokemons (some areas dosen't contain any pokemon, they should not inherit this class)
class ISpawnPokemon
{
public:
	virtual ~ISpawnPokemon() = default;

public:
	virtual Pokemon* SpawnPokemon() = 0;

protected:
	std::vector<SpawnPokes> pokesInThisZone;
};