#include "Pidgey.h"

bool Pidgey::OnPokemonCreate()
{
	if (!created)
	{
		front = new Sprite("Assets/Pokemons/Front/pidgey.png", SDL_ScaleMode::SDL_ScaleModeNearest);
		back = new Sprite("Assets/Pokemons/Back/pidgey.png", SDL_ScaleMode::SDL_ScaleModeNearest);
		type = Type::FLYING;
		type2 = Type::NORMAL;
		name = "Pidgey";

		InitStats(40, 45, 40, 35, 35, 56);
		learnMoves.push_back(LearnableMove(5, new Move(Moves::SAND_ATTACK, "Sand Attack", Type::GROUND, 100, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(12, new Move(Moves::QUICK_ATTACK, "Quick Attack", Type::NORMAL, 100, 40, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(19, new Move(Moves::WHIRLWIND, "Whirlwind", Type::NORMAL, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(28, new Move(Moves::WING_ATTACK, "Wing Attack", Type::FLYING, 100, 60, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(36, new Move(Moves::AGILITY, "Agility", Type::PSYCHIC, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(44, new Move(Moves::MIRROR_MOVE, "Mirror Move", Type::FLYING, 0, 0, Category::STATUS)));
		GenerateMoveset();
		hp = stats.MaxHP;
		return true;
	}
	return false;
}

void Pidgey::Evolve(int level)
{
}

void Pidgey::GenerateMoveset()
{
	if (stats.Level >= 1 && stats.Level < 5)
	{
		moveset[0] = new Move(Moves::GUST, "Gust", Type::FLYING, 100, 40, Category::PHYSICAL);
	}
	else if (stats.Level >= 5 && stats.Level < 12)
	{
		moveset[0] = new Move(Moves::GUST, "Gust", Type::FLYING, 100, 40, Category::PHYSICAL);
		moveset[1] = new Move(Moves::SAND_ATTACK, "Sand Attack", Type::GROUND, 100, 0, Category::STATUS);
	}
	else if (stats.Level >= 12 && stats.Level < 19)
	{
		moveset[0] = new Move(Moves::GUST, "Gust", Type::FLYING, 100, 40, Category::PHYSICAL);
		moveset[1] = new Move(Moves::SAND_ATTACK, "Sand Attack", Type::GROUND, 100, 0, Category::STATUS);
		moveset[2] = new Move(Moves::QUICK_ATTACK, "Quick Attack", Type::NORMAL, 100, 40, Category::PHYSICAL);
	}
	else if (stats.Level >= 19 && stats.Level < 28)
	{
		moveset[0] = new Move(Moves::GUST, "Gust", Type::FLYING, 100, 40, Category::PHYSICAL);
		moveset[1] = new Move(Moves::SAND_ATTACK, "Sand Attack", Type::GROUND, 100, 0, Category::STATUS);
		moveset[2] = new Move(Moves::QUICK_ATTACK, "Quick Attack", Type::NORMAL, 100, 40, Category::PHYSICAL);
		moveset[3] = new Move(Moves::WHIRLWIND, "Whirlwind", Type::NORMAL, 0, 0, Category::STATUS);
	}
	else if (stats.Level >= 28 && stats.Level < 36)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 2;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 36 && stats.Level < 44)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size() - 1;
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
	else if (stats.Level >= 44)
	{
		srand(time(0));
		int randnum = rand() % learnableMoves.size();
		for (int i = 0; i < 3; i++)
			if (moveset[i]->GetMove() != (Moves)randnum)
				moveset[i] = learnableMoves[randnum];
	}
}
