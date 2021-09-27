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
	~DialogManager();

public:
	static DialogManager* GetInstance();
	void ShowDialog(Dialog dialog);
	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }
private:
	void HandleUpdate();
	void DrawBox();
	void DrawText();
	void TypeDialog(std::string line);

private:
	bool isActive = false;
	int currentLine = 0;
	Text text;
	TTF_Font* font = nullptr;
	Sprite* mBox = nullptr;
	Dialog dialog;

private:
	SDL_Rect fontSize;
	std::thread t1;
};