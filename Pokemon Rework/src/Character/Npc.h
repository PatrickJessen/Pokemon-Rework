#pragma once
#include "Character.h"

class Npc : public Character
{
public:
	Npc(std::string name, std::string texturePath, int width, int height);
	~Npc();

public:
	void RandomMovement();
};