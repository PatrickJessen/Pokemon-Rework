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

	isTrainer = true;
}

Trainer::~Trainer()
{
	delete battleSprite;
}

void Trainer::Update(float elapsedTime)
{
	/*switch (animDir)
	{
	case AnimationDirection::DOWN:
		viewRect = { xPos + width / 2, yPos, 2, height * 5 };
		break;
	case AnimationDirection::UP:
		viewRect = { xPos + width / 2, yPos, 2, height * 5 };
		break;
	case AnimationDirection::LEFT:
		viewRect = { xPos + width / 2, yPos, 2 / 5, height };
		break;
	case AnimationDirection::RIGHT:
		viewRect = { xPos + width / 2, yPos, 2 * 5, height };
		break;
	default:
		break;
	}*/

	if (isSpotted)
		canWalk = false;

	SDL_RenderDrawRect(Window::GetRender(), &interactPoint);
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

void Trainer::AddBattleDialog(std::string message)
{
	battleDialog.Lines.push_back(message);
}
