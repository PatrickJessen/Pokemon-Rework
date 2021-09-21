#pragma once
#include "../Character/Character.h"
#include "../Character/Trainer.h"
#include "BattleHUD.h"
#include <thread>

enum class BattleState
{
	Start, PlayerAction, PlayerMove, EnemyMove, Death, SwitchPoke, Busy, Run, End, Stop
};

class BattleSystem
{
public:
	virtual ~BattleSystem() = 0;

public:
	virtual void SetupBattle() = 0;
	virtual void Update() = 0;
	virtual void PerformPlayerAttack() = 0;
	virtual void PerformEnemyAttack() = 0;
	virtual bool IGoFirst() = 0;
	virtual void EndBattle() = 0;

public:
	void PlayerAction();
	void PlayerMove();
	void HandleActionSelection();
	void HandleMoveSelection();
	Pokemon* GetNextHealthyPokemon();
	int PrioritiesEnemyMove(Pokemon* pokemon);
	int GetHighestDamageMove(Pokemon* pokemon);
	int IsEnemyMoveEffective(Pokemon* pokemon);

	int RandNum(int x, int y);

protected:
	Character* player;
	Pokemon* poke;
	BattleState state;
	BattleHUD bHud;
	int currentAction;
	int currentMove;
	std::string message;
	SDL_Rect playerHpBar;
	SDL_Rect enemyHpBar;
	int playerHpMaxWidth;
	int enemyHpMaxWidth;
	//std::thread* t;
	int timer = 0;
	bool iWon = false;
	bool end = false;
};