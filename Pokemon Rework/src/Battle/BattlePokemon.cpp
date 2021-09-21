#include "BattlePokemon.h"
//#include "../Core/Qoroutine.h"

BattlePokemon::BattlePokemon(Character* player, Pokemon* pokemon)
{
	this->player = player;
	this->poke = pokemon;
	pokemon->OnPokemonCreate();
	bHud.SetData();
	dynamic_cast<Trainer*>(player)->SetInBattlePokemon(GetNextHealthyPokemon());
	playerHpMaxWidth = 175;
	enemyHpMaxWidth = 175;
	enemyHpBar = { 417, 301, enemyHpMaxWidth, 10 };
	playerHpBar = { 895, 648, playerHpMaxWidth, 10 };
}

void BattlePokemon::SetupBattle()
{
	if (poke->GetHP() <= 0)
	{
		state = BattleState::End;
		iWon = true;
	}
	else if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon() == nullptr)
	{
		state = BattleState::End;
		iWon = false;
	}
}

void BattlePokemon::Update()
{
	SetupBattle();
	
	//SetupBattle();
	/*if (state == BattleState::EnemyMove)
		t = new std::thread(([this] {this->HandleEnemyAction(); }));*/

	UpdateUI();

	switch (state)
	{
	case BattleState::Start:
		message = "A wild " + poke->GetName() + " appeared";
		bHud.DrawTrainerEntrance(player);
		if (Input::KeyPressed(Key::SPACE))
		{
			state = BattleState::PlayerAction;
			message = "";
		}
		break;
	case BattleState::PlayerAction:
		PlayerAction();
		HandleActionSelection();
		break;
	case BattleState::PlayerMove:
	{
		PlayerMove();
		HandleMoveSelection();
		PerformPlayerAttack();
	}
		break;
	case BattleState::EnemyMove:
	{
		//StartQoroutine(20, &BattlePokemon::PerformEnemyAttack, this);
	}
		break;
	case BattleState::Busy:
		break;
	case BattleState::Death:
		if (bHud.AnimatePlayerDeath(dynamic_cast<Trainer*>(player)->GetInBattlePokemon()))
		{
			bHud.ClearMoveText(1);
			dynamic_cast<Trainer*>(player)->SetInBattlePokemon(GetNextHealthyPokemon());
			state = BattleState::SwitchPoke;
		}
		break;
	case BattleState::SwitchPoke:
		if (bHud.AnimateNextPlayerPokemon(dynamic_cast<Trainer*>(player)->GetInBattlePokemon()))
			state = BattleState::PlayerAction;
		break;
	case BattleState::Run:
		Run();
		break;
	case BattleState::End:
		EndBattle();
		break;
	case BattleState::Stop:
		//Stop
		break;
	default:
		break;
	}
}

void BattlePokemon::PerformPlayerAttack()
{
	if (Input::KeyPressed(Key::RETURN))
	{
		if (IGoFirst())
		{
			poke->TakeDamage(dynamic_cast<Trainer*>(player)->GetInBattlePokemon(), currentMove);
			//enemyHpBar.w = (poke->GetHP() * enemyHpMaxWidth) / poke->GetStats().MaxHP;
			message = dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetName() + " Used " + dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetMoveAt(currentMove)->GetMoveName();
			if (poke->GetHP() < 0)
				state = BattleState::End;
			else
			{
				state = BattleState::EnemyMove;
			}
		}
		else
		{
			state = BattleState::EnemyMove;
		}
	}
}

void BattlePokemon::PerformEnemyAttack()
{
	dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->TakeDamage(poke, PrioritiesEnemyMove(poke));
	message = poke->GetName() + " Used " + poke->GetMoveAt(PrioritiesEnemyMove(poke))->GetMoveName();
	if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetHP() < 0)
	{
		message = dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetName() + " Fainted!";
		state = BattleState::Death;
		//player->SetInBattlePokemon(GetNextHealthyPokemon());
	}
	else
		state = BattleState::PlayerAction;
}

bool BattlePokemon::IGoFirst()
{
	if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetStats().Speed >= poke->GetStats().Speed)
		return true;
	return false;
}

void BattlePokemon::EndBattle()
{
	if (iWon && !end)
	{
		message = poke->GetName() + " Fainted";
		end = true;
	}
	else if (!iWon && !end)
	{
		message = "You got no more pokemons left";
		end = true;
	}
}

void BattlePokemon::UpdateUI()
{
	if (state != BattleState::End || state != BattleState::Run)
	{
		bHud.DrawBattleFrame();

		bHud.DrawEnemyPokemonEntrance(poke);

		if (state != BattleState::Start)
		{
			bHud.DrawPlayerPokemonEntrance(dynamic_cast<Trainer*>(player)->GetInBattlePokemon());
			bHud.DrawPokemonBar(dynamic_cast<Trainer*>(player)->GetInBattlePokemon(), poke);
			bHud.DrawHealthBar(playerHpBar);
			bHud.DrawHealthBar(enemyHpBar);

			UpdateHealth();
		}
		//SDL_RenderPresent(Window::GetRender());
		//Window::Update();
	}
}

void BattlePokemon::UpdateHealth()
{
	enemyHpBar.w = (poke->GetHP() * enemyHpMaxWidth) / poke->GetStats().MaxHP;
	playerHpBar.w = (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetStats().MaxHP;
}

void BattlePokemon::Run()
{
	dynamic_cast<Trainer*>(player)->SetIsInBattle(false);
	end = true;
}
