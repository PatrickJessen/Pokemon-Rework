#include "Bulbasaur.h"

bool Bulbasaur::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/Bulbasaur1.png", SDL_ScaleMode::SDL_ScaleModeBest);
		back = new Sprite("Assets/Pokemons/Back/1.png", SDL_ScaleMode::SDL_ScaleModeBest);
		type = Type::GRASS;
		type2 = Type::POISON;
		name = "Bulbasaur";

		InitStats(45, 49, 49, 65, 65, 45);
		learnMoves.push_back(LearnableMove(7, new Move(Moves::LEECHSEED, "Leech Seed", Type::GRASS, 90, 0, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(13, new Move(Moves::VINEWHIP, "Vinewhip", Type::GRASS, 100, 45, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(20, new Move(Moves::POISONPOWDER, "Poison Powder", Type::POISON, 75, 0, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(27, new Move(Moves::RAZORLEAF, "Razorleaf", Type::GRASS, 90, 55, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(34, new Move(Moves::GROWTH, "Growth", Type::NORMAL, 0, 0, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(41, new Move(Moves::SLEEPPOWDER, "Sleep Powder", Type::GRASS, 75, 0, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(48, new Move(Moves::SOLARBEAM, "Solarbeam", Type::GRASS, 100, 120, Category::SPECIAL)));
		GenerateMoveset();
		hp = stats.MaxHP;
		created = true;
	}
	return created;
}

void Bulbasaur::Evolve(int level)
{
}

void Bulbasaur::GenerateMoveset()
{
	if (stats.Level >= 1 && stats.Level < 7)
	{
		moveset[0] = new Move(Moves::GROWL, "Growl", Type::NONE, 100, 0, Category::STATUS);
		moveset[1] = new Move(Moves::TACKLE, "Tackle", Type::NORMAL, 100, 40, Category::PHYSICAL);
	}
	else if (stats.Level >= 7 && stats.Level < 13)
		moveset[2] = new Move(Moves::LEECHSEED, "Leech Seed", Type::GRASS, 90, 0, Category::PHYSICAL);
	else if (stats.Level >= 13 && stats.Level < 20)
		moveset[3] = new Move(Moves::VINEWHIP, "Vinewhip", Type::GRASS, 100, 45, Category::PHYSICAL);
	else if (stats.Level >= 20 && stats.Level < 27)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 4;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 27 && stats.Level < 34)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 3;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 34 && stats.Level < 41)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 2;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 41 && stats.Level < 48)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 1;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 48)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size();
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
}