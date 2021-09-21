#pragma once
#include "BattleSystem.h"

class BattleTrainer : public BattleSystem
{
public:
	BattleTrainer(Character* player, Character* enemy);

public:
	virtual void SetupBattle() override;
	virtual void Update() override;
	virtual void PerformPlayerAttack() override;
	virtual void PerformEnemyAttack() override;
	virtual bool IGoFirst() override;
	virtual void EndBattle() override;

public:
	Pokemon* GetEnemyNextHealthyPokemon();


private:
	Character* enemy;

	std::vector<std::string> winningQuotes;
	std::vector<std::string> losingQuotes;
};