#pragma once
#include "../Core/Sprite.h"
#include "Moves/Move.h"
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include "LearnableMove.h"
#include "../Core/Random.h"

struct Stats
{
	int MaxHP;
	int Attack;
	int Defense;
	float SPATK;
	float SPDEF;
	int Speed;
	int Level;
};

class Pokemon
{
public:
	enum class GrowthRate { Fast, MediumFast };
	Pokemon();
	~Pokemon();

public:
	virtual bool OnPokemonCreate() = 0;
	virtual void Evolve(int level) = 0;
	virtual void GenerateMoveset() = 0;

	void OnUpdate();
	void InitStats(int hp, int attack, int defense, float spAtk, float spDef, int speed);
	void LevelUp();

	void Attack();
	bool TakeDamage(Pokemon* attacker, int x);

public:
	void RefreshHP() { hp = stats.MaxHP; }
	int GetLevel();
	int GetHP();
	std::string GetName();
	std::string GetMoveName();
	Sprite* GetFrontTexture() { return front; }
	Sprite* GetBackTexture() { return back; }
	SDL_Rect GetPosition() { return pokeRect; }
	Type GetType() { return type; }
	Type GetType2() { return type2; }
	Stats GetStats() { return stats; }
	void SetHP(int value) { hp += value; }
	Move* GetMoveSet(int x) { return moveset[x]; }
	void SetCurrentMove(int x) { currentMove = moveset[x]; }
	std::vector<Move*> GetMoves();
	Move* GetMoveAt(int x) { return moveset[x]; }
	void AddLevel();
	void SetLevel(int value) { stats.Level = value; }
	int GetExp() { return experience; }
	void SetExp(int value) { experience += value; }
	GrowthRate growthRate;
	int GetExpForLevel(int level);
	int GetRequiredExp() { return requiredExp; }
	int GetExpYield() { return expYield; }

	std::string name;



protected:
	std::unique_ptr<Pokemon> evolution = nullptr;
	std::map<int, Move*> learnableMoves;
	std::vector<LearnableMove> learnMoves;
	Stats stats;
	Type type;
	Type type2;
	SDL_Rect pokeRect;
	Sprite* front;
	Sprite* back;
	bool created = false;
	bool isInBattle = false;
	Move* moveset[4];
	Move* currentMove = nullptr;
	int hp;
	int experience;
	int requiredExp;
	int expYield;

private:
	void InitMultipliers();
};