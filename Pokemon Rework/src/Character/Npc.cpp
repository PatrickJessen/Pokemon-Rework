#include "Npc.h"

Npc::Npc(std::string name, std::string texturePath, int width, int height)
{
	this->name = name;
	this->texturePath = texturePath;
	this->width = width;
	this->height = height;
	sprite = new Sprite(texturePath, SDL_ScaleMode::SDL_ScaleModeNearest);
}

Npc::~Npc()
{
}
