#pragma once
#include "Character.h"

class Npc : public Character
{
public:
	Npc(std::string name, std::string texturePath, int width, int height, int srcW, int srcH);
	~Npc();

public:
	virtual void Update(float elapsedTime) override;
	void RandomMovement();
};