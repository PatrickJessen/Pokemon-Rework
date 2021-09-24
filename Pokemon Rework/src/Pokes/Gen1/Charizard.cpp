#include "Charizard.h"

bool Charizard::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/charizard.png", SDL_ScaleMode::SDL_ScaleModeBest);
		back = new Sprite("Assets/Pokemons/Back/charizard.png", SDL_ScaleMode::SDL_ScaleModeBest);
		type = Type::FIRE;
		type2 = Type::FLYING;
		name = "Charizard";

		InitStats(78, 84, 78, 109, 85, 99);
		learnMoves.push_back(LearnableMove(9, new Move(Moves::EMBER, "Ember", Type::FIRE, 100, 40, Category::SPECIAL)));
		learnMoves.push_back(LearnableMove(15, new Move(Moves::LEER, "Leer", Type::NORMAL, 100, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(22, new Move(Moves::RAGE, "Rage", Type::NORMAL, 100, 20, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(30, new Move(Moves::SLASH, "Slash", Type::NORMAL, 100, 70, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(38, new Move(Moves::FLAMETHROWER, "Flamethrower", Type::FIRE, 100, 90, Category::SPECIAL)));
		learnMoves.push_back(LearnableMove(46, new Move(Moves::FIRESPIN, "Firespin", Type::FIRE, 85, 35, Category::SPECIAL)));
		GenerateMoveset();
		hp = stats.MaxHP;
		return created = true;
	}
	return created = false;
}

void Charizard::Evolve(int level)
{
}

void Charizard::GenerateMoveset()
{
	moveset[0] = new Move(Moves::FLAMETHROWER, "Flamethrower", Type::FIRE, 100, 90, Category::SPECIAL);
}