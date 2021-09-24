#pragma once
#include "Character.h"
#include "../Pokes/Pokemon.h"


class Trainer : public Character
{
public:
	Trainer(std::string name, std::string texturePath, std::string battleTexturePath, int width, int height, int srcX, int srcY, int money);
	~Trainer();

public:
	virtual void Update(float elapsedTime) override;

public:
	bool IsWholeTeamDead();
	void SetViewRect(int x, int y) { viewRect.x - x; viewRect.y - y; }
	void SetIsInTrainerBattle(bool value) { isInTrainerBattle = value; }
	void SetIsInPokemonBattle(bool value) { isInPokemonBattle = value; }
	void SetIsDefeated(bool value) { isDefeated = value; }
	void SetInBattlePokemon(Pokemon* value) { inBattlePokemon = value; }
	void AddPokemonToBag(Pokemon* pokemon);
	void AddPokemonToPc(Pokemon* pokemon);
	void SetStarterPoke(Pokemon* pokemon) { starterPoke = pokemon; }
	bool GetIsDefeated() { return isDefeated; }
	bool GetIsInTrainerBattle() { return isInTrainerBattle; }
	bool GetIsInPokemonBattle() { return isInPokemonBattle; }
	SDL_Rect& GetViewRect() { return viewRect; }
	int GetSizeOfPokebag() { return sizeOfPokebag; }
	Pokemon* GetInBattlePokemon() { return inBattlePokemon; }
	Pokemon* GetPokemonAtIndex(int i);
	Pokemon* GetPokemonByName(const char* pokemonName);
	Pokemon* GetStarterPoke() { return starterPoke; }
	Pokemon* GetPokeBag() { return pokebag[5]; }
	Sprite* GetBattleTexture() { return battleSprite; }
	Dialog GetBattleDialog() { return battleDialog; }
	void AddBattleDialog(std::string message);
	void SetIsSpottet(bool value) { isSpotted = value; }
	bool GetIsSpottet() { return isSpotted; }

public:
	int GetMoney() { return money; }


public:
	void SetMoney(int value) { money = value; }

	SDL_Rect viewRect;
private:
	std::string battleTexturePath;
	Sprite* battleSprite = nullptr;
	int money = 100;
	bool isInTrainerBattle = false;
	bool isInPokemonBattle = false;
	bool isDefeated = false;
	int sizeOfPokebag = 0;
	Pokemon* inBattlePokemon = nullptr;
	Pokemon* pokebag[5];
	Pokemon* starterPoke = nullptr;
	std::vector<Pokemon*> pc;
	int timer = 0;
	int xOverflow = 0;
	int yOverflow = 0;
	int step = 0;
	bool isSpotted = false;

	Dialog battleDialog;
};