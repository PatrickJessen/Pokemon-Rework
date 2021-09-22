#include "BattlePokemon.h"
//#include "../Core/Qoroutine.h"

BattlePokemon::BattlePokemon(Character* player, Pokemon* pokemon)
{
	this->player = static_cast<Trainer*>(player);
	this->poke = pokemon;
	pokemon->OnPokemonCreate();
	bHud.SetData();
	this->player->SetInBattlePokemon(GetNextHealthyPokemon());
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
	else if (player->GetInBattlePokemon() == nullptr)
	{
		state = BattleState::End;
		iWon = false;
	}
}

void BattlePokemon::Update()
{
	SetupBattle();

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
	case BattleState::Busy:
		break;
	case BattleState::Death:
		if (bHud.AnimatePlayerDeath(player->GetInBattlePokemon()))
		{
			bHud.ClearMoveText(1);
			player->SetInBattlePokemon(GetNextHealthyPokemon());
			state = BattleState::SwitchPoke;
		}
		break;
	case BattleState::SwitchPoke:
		if (bHud.AnimateNextPlayerPokemon(player->GetInBattlePokemon()))
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
			poke->TakeDamage(player->GetInBattlePokemon(), currentMove);
			//enemyHpBar.w = (poke->GetHP() * enemyHpMaxWidth) / poke->GetStats().MaxHP;
			message = player->GetInBattlePokemon()->GetName() + " Used " + player->GetInBattlePokemon()->GetMoveAt(currentMove)->GetMoveName();
			if (poke->GetHP() < 0)
				state = BattleState::End;
			else
			{
				t1 = std::thread(&BattlePokemon::PerformEnemyAttack, this);
			}
		}
		else
		{
			t1 = std::thread(&BattlePokemon::PerformEnemyAttack, this);
		}
	}
}

void BattlePokemon::PerformEnemyAttack()
{
	player->GetInBattlePokemon()->TakeDamage(poke, PrioritiesEnemyMove(poke));
	message = poke->GetName() + " Used " + poke->GetMoveAt(PrioritiesEnemyMove(poke))->GetMoveName();
	if (player->GetInBattlePokemon()->GetHP() < 0)
	{
		message = player->GetInBattlePokemon()->GetName() + " Fainted!";
		state = BattleState::Death;
		//player->SetInBattlePokemon(GetNextHealthyPokemon());
	}
	else
		state = BattleState::PlayerAction;
}

bool BattlePokemon::IGoFirst()
{
	if (player->GetInBattlePokemon()->GetStats().Speed >= poke->GetStats().Speed)
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

	if (Input::KeyPressed(Key::SPACE))
	{
		player->SetIsInBattle(false);
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
			bHud.DrawPlayerPokemonEntrance(player->GetInBattlePokemon());
			bHud.DrawPokemonBar(player->GetInBattlePokemon(), poke);
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
	playerHpBar.w = (player->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / player->GetInBattlePokemon()->GetStats().MaxHP;
}

void BattlePokemon::Run()
{
	player->SetIsInBattle(false);
	end = true;
}
