#include "Charmander.h"

bool Charmander::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/Charmander.png", SDL_ScaleMode::SDL_ScaleModeBest);
		back = new Sprite("Assets/Pokemons/Back/4.png", SDL_ScaleMode::SDL_ScaleModeBest);
		type = Type::FIRE;
		name = "Charmander";

		InitStats(39, 52, 43, 60, 50, 65);
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

void Charmander::Evolve(int level)
{
	if (GetLevel() == level)
	{
		//evolution = new Charmeleon();
	}
}

void Charmander::GenerateMoveset()
{
	if (stats.Level >= 1 && stats.Level < 9)
	{
		moveset[0] = new Move(Moves::GROWL, "Growl", Type::NONE, 100, 0, Category::STATUS);
		moveset[1] = new Move(Moves::SCRATCH, "Scratch", Type::NORMAL, 100, 40, Category::PHYSICAL);
		moveset[2] = new Move(Moves::EMBER, "Ember", Type::FIRE, 100, 40, Category::SPECIAL);
	}
	else if (stats.Level >= 9 && stats.Level < 15)
		moveset[2] = new Move(Moves::EMBER, "Ember", Type::FIRE, 100, 40, Category::SPECIAL);
	else if (stats.Level >= 15 && stats.Level < 22)
		moveset[3] = new Move(Moves::LEER, "Leer", Type::NORMAL, 100, 0, Category::STATUS);
	else if (stats.Level >= 22 && stats.Level < 30)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 3;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 30 && stats.Level < 38)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 2;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 38 && stats.Level < 46)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 1;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 46)
	{
		srand(time(0));
		for (int i = 0; i < 4; i++)
		{
			int randnum = rand() % learnMoves.size();
			if (moveset[i] == nullptr)
				for (int j = 0; j < 4; j++)
					if (moveset[i] != learnMoves[randnum].move)
						moveset[i] = learnMoves[randnum].move;
		}
	}
}
