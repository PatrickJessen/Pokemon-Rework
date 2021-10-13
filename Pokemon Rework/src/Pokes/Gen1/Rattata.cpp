#include "Rattata.h"

bool Rattata::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/rattata.png", SDL_ScaleMode::SDL_ScaleModeNearest);
		back = new Sprite("Assets/Pokemons/Back/rattata.png", SDL_ScaleMode::SDL_ScaleModeNearest);
		type = Type::NORMAL;
		name = "Rattata";

		InitStats(30, 56, 35, 25, 35, 72);
		learnMoves.push_back(LearnableMove(7, new Move(Moves::QUICK_ATTACK, "Quick Attack", Type::NORMAL, 100, 40, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(14, new Move(Moves::HYPER_FANG, "Hyper Fang", Type::NORMAL, 90, 80, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(23, new Move(Moves::FOCUS_ENERGY, "Focus Energy", Type::NORMAL, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(34, new Move(Moves::SUPER_FANG, "Super Fang", Type::NORMAL, 90, 0, Category::PHYSICAL)));
		GenerateMoveset();
		expYield = 64;
		hp = stats.MaxHP;
		return created = true;
	}
	return created = false;
}

void Rattata::Evolve(int level)
{
}

void Rattata::GenerateMoveset()
{
	if (stats.Level >= 1 && stats.Level < 7)
	{
		moveset[0] = new Move(Moves::TACKLE, "Tackle", Type::NORMAL, 100, 40, Category::PHYSICAL);
		moveset[1] = new Move(Moves::TAILWHIP, "Tailwhip", Type::NORMAL, 100, 0, Category::STATUS);
	}
	else if (stats.Level >= 7 && stats.Level < 14)
		moveset[2] = new Move(Moves::QUICK_ATTACK, "Quick Attack", Type::NORMAL, 100, 40, Category::PHYSICAL);
	else if (stats.Level >= 14 && stats.Level < 23)
		moveset[3] = new Move(Moves::HYPER_FANG, "Hyper fang", Type::NORMAL, 90, 80, Category::PHYSICAL);
	else if (stats.Level >= 23 && stats.Level < 34)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 1;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 34)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size();
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
}
