#pragma once
#include <string>
#include "../Pokes/Pokemon.h"
#include "../Character/Trainer.h"
#include "SDL_ttf.h"
#include "../UI/Text.h"


class BattleHUD
{
public:
	void SetData();
	void DrawBattleFrame();
	void DrawTrainerEntrance(Trainer* trainer);
	void DrawEnemyTrainerEntrance(Trainer* enemy);
	void DrawEnemyPokemonEntrance(Pokemon* enemy);
	void DrawEntrance(Trainer* trainer, Pokemon* opponent);
	void DrawPlayerPokemonEntrance(Pokemon* player);
	void DrawEnemyTrainerPokemonEntrance(Pokemon* opponent);
	void DrawPokemonBar(Pokemon* player, Pokemon* opponent);
	void DrawHealthBar(SDL_Rect rect);
	void DrawOptions();
	void DrawMoves(Pokemon* pokemon);
	void DrawHelper(int count, Text* text);
	void DrawText(Text pokeText, SDL_Rect fontRect);

	void UpdateActionSelection(int action);
	void UpdateActionSelection(int action, int moveCount);
	void ClearText();

	void ClearMoveText(int index);

//Animation
	bool AnimatePlayerDeath(Pokemon* pokemon);
	bool AnimateEnemyDeath(Pokemon* pokemon);
	bool AnimateNextPlayerPokemon(Pokemon* pokemon);

public:
	void SetFGColor(int r, int g, int b) { fGColor.r = r; fGColor.g = g; fGColor.b = b; }
	SDL_Color GetColor() { return fGColor; }

private:
	std::string pokeLevel;
	SDL_Color fGColor;
	SDL_Color bGColor;
	TTF_Font* font;
	SDL_Rect fontSize;
	Text optionText[4];
	Text moveText[4];
	Text pokeName;
	Text enemyPokeName;
	SDL_Rect trainerRect = { 390, 587, 200, 100 }; //587
	SDL_Rect opponentRect = { 890, 350, 200, 150 };
	SDL_Rect pokeRect = { 390, 608, 200, 100 };
	SDL_Rect opponenPoketRect = { 890, 350, 200, 150 };
	int timer = 0;
};