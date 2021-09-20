#pragma once
#include "Character.h"

class Trainer : public Character
{
public:
	Trainer(std::string name, std::string texturePath, std::string battleTexturePath, int width, int height, int money);
	~Trainer();

public:
	void WalkUp();
	void WalkDown();
	void WalkLeft();
	void WalkRight();

public:
	int GetMoney() { return money; }

public:
	void SetMoney(int value) { money = value; }

private:
	std::string battleTexturePath;
	Sprite* battleSprite = nullptr;
	int money = 100;
};