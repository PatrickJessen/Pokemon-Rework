#pragma once
#include <string>
#include "SDL_ttf.h"
#include "../UI/Text.h"
#include "../Core/Sprite.h"
class BattleDialog
{
public:
	BattleDialog();

	void ShowDialog(std::string message);

private:
	void DrawBox();
	void TypeDialog(std::string line);

private:
	Text text;
	TTF_Font* font = nullptr;
	Sprite* mBox = nullptr;

private:
	SDL_Rect fontSize;
};