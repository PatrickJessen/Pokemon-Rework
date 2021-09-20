#include "Trainer.h"

Trainer::Trainer(std::string name, std::string texturePath, std::string battleTexturePath, int width, int height, int money)
{
	this->name = name;
	this->texturePath = texturePath;
	this->battleTexturePath = battleTexturePath;
	this->width = width;
	this->height = height;
	this->money = money;
	sprite = new Sprite(texturePath, SDL_ScaleMode::SDL_ScaleModeNearest);
	battleSprite = new Sprite(battleTexturePath, SDL_ScaleMode::SDL_ScaleModeNearest);

	position = { xPos, yPos, width, height };
	collisionPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 10 };
	srcRect = { 0, 0, 62, 65 };
}

Trainer::~Trainer()
{
	delete battleSprite;
}

void Trainer::WalkUp()
{
	//speed = 1;
	if (Input::KeyState(Key::LSHIFT))
		yPos -= speed + 5;
	else
		yPos -= (int)(speed * Window::GetDeltatime());
}

void Trainer::WalkDown()
{
	if (Input::KeyState(Key::LSHIFT))
		yPos += speed + 5;
	else
		yPos += (int)(speed * Window::GetDeltatime());
}

void Trainer::WalkLeft()
{
	if (Input::KeyState(Key::LSHIFT))
		xPos -= speed + 5;
	else
		xPos -= (int)(speed * Window::GetDeltatime());
}

void Trainer::WalkRight()
{
	if (Input::KeyState(Key::LSHIFT))
		xPos += speed + 5;
	else
		xPos += (int)(speed * Window::GetDeltatime());
}
