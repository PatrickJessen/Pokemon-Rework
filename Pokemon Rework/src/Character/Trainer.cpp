#include "Trainer.h"

Trainer::Trainer(std::string name, std::string texturePath, std::string battleTexturePath, int width, int height, int srcX, int srcY, int money)
{
	this->name = name;
	this->texturePath = texturePath;
	this->battleTexturePath = battleTexturePath;
	this->width = width;
	this->height = height;
	this->money = money;
	SetSrcRect(0, 0, srcX, srcY);
	sprite = new Sprite(texturePath, SDL_ScaleMode::SDL_ScaleModeNearest);
	battleSprite = new Sprite(battleTexturePath, SDL_ScaleMode::SDL_ScaleModeNearest);

	position = { xPos, yPos, width, height };
	collisionPoint = { xPos + width / 2, yPos + height / 2 + 5, 10, 10 };

	isTrainer = true;
}

Trainer::~Trainer()
{
	delete battleSprite;
}

void Trainer::Update()
{
	switch (animDir)
	{
	case AnimationDirection::DOWN:
		viewRect = { xPos, yPos, width, height * 5 };
		break;
	case AnimationDirection::UP:
		viewRect = { xPos, yPos, width, height * 5 };
		break;
	case AnimationDirection::LEFT:
		viewRect = { xPos, yPos, width / 5, height };
		break;
	case AnimationDirection::RIGHT:
		viewRect = { xPos, yPos, width * 5, height };
		break;
	default:
		break;
	}
	yOverflow += -1 / Window::GetDeltatime();

	//if (yPos % 64 == 0)
	//	return;
	//step = 64 / (SDL_GetTicks() / 1000);
	//SDL_RenderDrawRect(Window::GetRender(), &viewRect);
}

bool Trainer::IsWholeTeamDead()
{
	int deathCounter = 0;
	for (int i = 0; i < sizeOfPokebag; i++)
	{
		if (pokebag[i]->GetHP() <= 0)
			deathCounter++;
	}
	if (deathCounter == sizeOfPokebag)
		return true;
	return false;
}

void Trainer::WalkUp()
{
	//speed = 1;
	if (canWalk)
	{
		if (Input::KeyState(Key::LSHIFT))
			yPos -= speed + 5;
		else
		{
			if (yOverflow <= -64)
			{
				yPos -= 64;
				yOverflow = 0;
			}
		}
	}
}

void Trainer::WalkDown()
{
	if (canWalk)
		if (Input::KeyState(Key::LSHIFT))
			yPos += speed + 5;
		else
			yPos += (int)(speed * Window::GetDeltatime());
}

void Trainer::WalkLeft()
{
	if (canWalk)
		if (Input::KeyState(Key::LSHIFT))
			xPos -= speed + 5;
		else
			xPos -= (int)(speed * Window::GetDeltatime());
}

void Trainer::WalkRight()
{
	if (canWalk)
		if (Input::KeyState(Key::LSHIFT))
			xPos += speed + 5;
		else
			xPos += (int)(speed * Window::GetDeltatime());
}

void Trainer::AddPokemonToBag(Pokemon* pokemon)
{
	for (int i = 0; i < 5; i++)
		if (pokebag[i] == nullptr)
		{
			pokebag[i] = pokemon;
			sizeOfPokebag++;
			return;
		}
}

void Trainer::AddPokemonToPc(Pokemon* pokemon)
{
	pc.push_back(pokemon);
}

Pokemon* Trainer::GetPokemonAtIndex(int i)
{
	return pokebag[i];
}

Pokemon* Trainer::GetPokemonByName(const char* pokemonName)
{
	for (int i = 0; i < 5; i++)
		if (pokebag[i] != nullptr)
			if (pokemonName == pokebag[i]->GetName())
				return pokebag[i];
}
