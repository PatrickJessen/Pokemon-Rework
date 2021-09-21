#include "Npc.h"

Npc::Npc(std::string name, std::string texturePath, int width, int height, int srcW, int srcH)
{
	this->name = name;
	this->texturePath = texturePath;
	this->width = width;
	this->height = height;
	sprite = new Sprite(texturePath, SDL_ScaleMode::SDL_ScaleModeNearest);
	SetSrcRect(0, 0, srcW, srcH);
}

Npc::~Npc()
{
}

void Npc::Update()
{
}
