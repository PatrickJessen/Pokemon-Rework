#pragma once
#include "../Pokemon.h"

class Squirtle : public Pokemon
{
public:
	Squirtle(int level) : Pokemon() { this->stats.Level = level; }

public:
	virtual bool OnPokemonCreate() override;
	virtual void Evolve(int level) override;
	virtual void GenerateMoveset() override;
};