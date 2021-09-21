#pragma once
#include "Character.h"
#include "../Pokes/Pokemon.h"

class Trainer : public Character
{
public:
	Trainer(std::string name, std::string texturePath, std::string battleTexturePath, int width, int height, int srcX, int srcY, int money);
	~Trainer();

public:
	virtual void Update() override;

public:
	bool IsWholeTeamDead();
	void WalkUp();
	void WalkDown();
	void WalkLeft();
	void WalkRight();
	void SetViewRect(int x, int y) { viewRect.x - x; viewRect.y - y; }
	void SetIsInBattle(bool value) { isInBattle = value; }
	void SetIsDefeated(bool value) { isDefeated = value; }
	void SetInBattlePokemon(Pokemon* value) { inBattlePokemon = value; }
	void AddPokemonToBag(Pokemon* pokemon);
	void AddPokemonToPc(Pokemon* pokemon);
	void SetStarterPoke(Pokemon* pokemon) { starterPoke = pokemon; }
	bool GetIsDefeated() { return isDefeated; }
	bool GetIsInBattle() { return isInBattle; }
	SDL_Rect& GetViewRect() { return viewRect; }
	int GetSizeOfPokebag() { return sizeOfPokebag; }
	Pokemon* GetInBattlePokemon() { return inBattlePokemon; }
	Pokemon* GetPokemonAtIndex(int i);
	Pokemon* GetPokemonByName(const char* pokemonName);
	Pokemon* GetStarterPoke() { return starterPoke; }
	Pokemon* GetPokeBag() { return pokebag[5]; }
	Sprite* GetBattleTexture() { return battleSprite; }

public:
	int GetMoney() { return money; }

public:
	void SetMoney(int value) { money = value; }

private:
	std::string battleTexturePath;
	Sprite* battleSprite = nullptr;
	int money = 100;
	SDL_Rect viewRect;
	bool isInBattle = false;
	bool isDefeated = false;
	int sizeOfPokebag = 0;
	Pokemon* inBattlePokemon = nullptr;
	Pokemon* pokebag[5];
	Pokemon* starterPoke = nullptr;
	std::vector<Pokemon*> pc;
};