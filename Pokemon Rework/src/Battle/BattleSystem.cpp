#include "BattleSystem.h"
#include <chrono>
#include "../Pokes/TypeChart.h"

BattleSystem::~BattleSystem()
{
	delete poke;
}

void BattleSystem::PlayerAction()
{
	state = BattleState::PlayerAction;
	bHud.DrawOptions();
}

void BattleSystem::PlayerMove()
{
	bHud.DrawMoves(player->GetInBattlePokemon());
}


void BattleSystem::HandleActionSelection()
{
	if (Input::KeyPressed(Key::S))
		if (currentAction < 3)
			++currentAction;
	if (Input::KeyPressed(Key::W))
		if (currentAction > 0)
			--currentAction;

	bHud.UpdateActionSelection(currentAction);

	if (Input::KeyPressed(Key::RETURN))
		if (currentAction == 0)
		{
			state = BattleState::PlayerMove;
		}
		else if (currentAction == 1)
		{
			//Items
		}
		else if (currentAction == 2)
		{
			state = BattleState::SwitchPoke;
		}
		else if (currentAction == 3)
		{
			state = BattleState::Run;
		}

}

void BattleSystem::HandleMoveSelection()
{
	if (Input::KeyPressed(Key::S))
		if (currentMove < player->GetInBattlePokemon()->GetMoves().size() - 1)
			++currentMove;
	if (Input::KeyPressed(Key::W))
		if (currentMove > 0)
			--currentMove;
	
	bHud.UpdateActionSelection(currentMove, player->GetInBattlePokemon()->GetMoves().size());
}

Pokemon* BattleSystem::GetNextHealthyPokemon()
{
	for (int i = 0; i < 4; i++)
	{
		if (player->GetPokemonAtIndex(i) != nullptr && player->GetPokemonAtIndex(i)->GetHP() > 0)
		{
			message = "Go " + player->GetPokemonAtIndex(i)->GetName();
			return player->GetPokemonAtIndex(i);
		}
	}
	return nullptr;
}

int BattleSystem::PrioritiesEnemyMove(Pokemon* pokemon)
{
	for (int i = 0; i < pokemon->GetMoves().size(); i++)
	{
		if (IsEnemyMoveEffective(pokemon) != 0)
		{
			int x = rand() % 100;
			if (x < 90)
				return IsEnemyMoveEffective(pokemon);
			else
				return rand() % pokemon->GetMoves().size();
		}
		else if (pokemon->GetMoveAt(i)->GetDamage() == GetHighestDamageMove(pokemon))
		{
			int x = rand() % 100;
			if (x < 80)
				return i;
			else
				return rand() % pokemon->GetMoves().size();
		}
	}
	int x = rand() % pokemon->GetMoves().size();
	return x;
}

int BattleSystem::GetHighestDamageMove(Pokemon* pokemon)
{
	int highestDamage = 0;
	for (int i = 0; i < pokemon->GetMoves().size(); i++)
	{
		if (highestDamage < pokemon->GetMoveAt(i)->GetDamage())
			highestDamage = pokemon->GetMoveAt(i)->GetDamage();
	}
	return highestDamage;
}

int BattleSystem::IsEnemyMoveEffective(Pokemon* pokemon)
{
	for (int i = 0; i < pokemon->GetMoves().size(); i++)
		if (TypeChart::GetEffectiveness(pokemon->GetMoveAt(i)->GetType(), player->GetInBattlePokemon()->GetType()) == 2.0f)
			return i;
	return 0;
}

void BattleSystem::GainExp(Pokemon* enemy)
{
	int expYield = enemy->GetExpYield();
	int enemyLevel = enemy->GetLevel();

	float trainerBonus = (player->GetIsInTrainerBattle()) ? 1.5f : 1.0f;

	int expGain = (expYield * enemyLevel * trainerBonus) / 7;
	player->GetInBattlePokemon()->SetExp(expGain);
}

int BattleSystem::RandNum(int x, int y)
{
	return x + (rand() / (RAND_MAX / (y - x)));
}
