#include "Squirtle.h"

bool Squirtle::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/Squirtle.png", SDL_ScaleMode::SDL_ScaleModeBest);
		back = new Sprite("Assets/Pokemons/Back/7.png", SDL_ScaleMode::SDL_ScaleModeBest);
		type = Type::WATER;
		name = "Squirtle";

		InitStats(44, 48, 65, 50, 64, 43);
		learnMoves.push_back(LearnableMove(8, new Move(Moves::BUBBLE, "Bubble", Type::WATER, 100, 40, Category::SPECIAL)));
		learnMoves.push_back(LearnableMove(15, new Move(Moves::WATERGUN, "Watergun", Type::WATER, 100, 40, Category::SPECIAL)));
		learnMoves.push_back(LearnableMove(22, new Move(Moves::BITE, "Bite", Type::DARK, 100, 60, Category::SPECIAL)));
		learnMoves.push_back(LearnableMove(28, new Move(Moves::WITHDRAW, "Withdraw", Type::WATER, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(35, new Move(Moves::SKULLBASH, "Skullbash", Type::NORMAL, 100, 130, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(42, new Move(Moves::HYDROPUMP, "Hydropump", Type::WATER, 80, 110, Category::SPECIAL)));

		GenerateMoveset();
		hp = stats.MaxHP;
		expYield = 64;
		requiredExp = GetExpForLevel(stats.Level);
		return created = true;
	}
	return created = false;
}

void Squirtle::Evolve(int level)
{
}

void Squirtle::GenerateMoveset()
{
	if (stats.Level >= 1 && stats.Level < 8)
	{
		moveset[0] = new Move(Moves::TAILWHIP, "Tailwhip", Type::NONE, 100, 0, Category::STATUS);
		moveset[1] = new Move(Moves::TACKLE, "Tackle", Type::NORMAL, 100, 40, Category::PHYSICAL);
	}
	else if (stats.Level >= 8 && stats.Level < 15)
		moveset[2] = new Move(Moves::BUBBLE, "Bubble", Type::WATER, 100, 40, Category::SPECIAL);
	else if (stats.Level >= 15 && stats.Level < 22)
		moveset[3] = new Move(Moves::BITE, "Bite", Type::DARK, 100, 60, Category::SPECIAL);
	else if (stats.Level >= 22 && stats.Level < 28)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 3;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 28 && stats.Level < 35)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 2;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 35 && stats.Level < 42)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 1;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 42)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size();
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
}