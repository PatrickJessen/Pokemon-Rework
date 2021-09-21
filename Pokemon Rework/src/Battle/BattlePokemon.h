#pragma once
#include "BattleSystem.h"

class BattlePokemon : public BattleSystem
{
public:
	BattlePokemon(Character* player, Pokemon* pokemon);
	BattlePokemon() = default;

public:
	virtual void SetupBattle() override;
	virtual void Update() override;
	virtual void PerformPlayerAttack() override;
	virtual void PerformEnemyAttack() override;
	virtual bool IGoFirst() override;
	virtual void EndBattle() override;

	void UpdateUI();

private:
	void UpdateHealth();
	void Run();


private:
	Pokemon* pokemon;
};