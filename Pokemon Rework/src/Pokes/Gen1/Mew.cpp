#include "Mew.h"

bool Mew::OnPokemonCreate()
{
	if (!created)
	{
		if (Random::InRange(0, 100) < 50)
		{
			front = new Sprite("Assets/Pokemons/Front/mew.png", SDL_ScaleMode::SDL_ScaleModeBest);
			back = new Sprite("Assets/Pokemons/Back/mew.png", SDL_ScaleMode::SDL_ScaleModeBest);
			name = "Mew";

		}
		else
		{
			front = new Sprite("Assets/Pokemons/Front/shinyMew.png", SDL_ScaleMode::SDL_ScaleModeBest);
			back = new Sprite("Assets/Pokemons/Back/shinyMew.png", SDL_ScaleMode::SDL_ScaleModeBest);
			name = "S Mew";
		}

		type = Type::PSYCHIC;

		InitStats(100, 100, 100, 100, 100, 100);
		learnMoves.push_back(LearnableMove(1, new Move(Moves::POUND, "Pound", Type::NORMAL, 100, 40, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(10, new Move(Moves::TRANSFORM, "Transform", Type::NORMAL, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(20, new Move(Moves::MEGA_PUNCH, "Mega Punch", Type::NORMAL, 85, 80, Category::PHYSICAL)));
		learnMoves.push_back(LearnableMove(30, new Move(Moves::METRONOME, "Metronome", Type::NORMAL, 0, 0, Category::STATUS)));
		learnMoves.push_back(LearnableMove(40, new Move(Moves::PSYCHIC, "Psychic", Type::PSYCHIC, 100, 90, Category::SPECIAL)));
		GenerateMoveset();
		hp = stats.MaxHP;
		return created = true;
	}
	return created = false;
}

void Mew::Evolve(int level)
{
}

void Mew::GenerateMoveset()
{
	moveset[0] = new Move(Moves::POUND, "Pound", Type::NORMAL, 100, 40, Category::PHYSICAL);
	moveset[1] = new Move(Moves::MEGA_PUNCH, "Mega Punch", Type::NORMAL, 85, 80, Category::PHYSICAL);
	moveset[2] = new Move(Moves::PSYCHIC, "Psychic", Type::PSYCHIC, 100, 90, Category::SPECIAL);
}