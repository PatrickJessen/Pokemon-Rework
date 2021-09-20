#pragma once
#include "Dialog.h"
#include "../UI/Text.h"
#include "SDL_ttf.h"
#include "../Core/Sprite.h"
#include <thread>

class DialogManager
{
public:
	DialogManager();

public:
	void ShowDialog(Dialog dialog);
	void HandleUpdate();
	void DrawBox();
	void TypeDialog(std::string line);
	void SetIsActive(bool value) { isActive = value; }

private:
	bool isActive = false;
	int currentLine = 0;
	Text text;
	TTF_Font* font = nullptr;
	Sprite* mBox = nullptr;
	Dialog dialog;

private:
	SDL_Rect fontSize;
};