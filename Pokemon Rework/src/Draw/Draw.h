#pragma once
#include "../Map/Map.h"
#include "../Character/Character.h"
#include "../Camera/Camera.h"

class Draw
{
public:
	Draw();
	~Draw();
public:
	void Update(Map* map, Character* character);

private:
	void DrawMapImage();
	void DrawMapBackground();
	void DrawMapForeground();

	void DrawCharacter();
	void DrawNpcCharacters();

private:
	Map* map = nullptr;
	Character* character = nullptr;
};