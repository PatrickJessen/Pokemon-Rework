#include "BattleTrainer.h"

BattleTrainer::BattleTrainer(Character* player, Character* enemy)
{
	this->player = player;
	this->enemy = enemy;
	bHud.SetData();
	dynamic_cast<Trainer*>(enemy)->SetInBattlePokemon(GetEnemyNextHealthyPokemon());
	dynamic_cast<Trainer*>(player)->SetInBattlePokemon(GetNextHealthyPokemon());
	playerHpMaxWidth = 175;
	enemyHpMaxWidth = 175;
	enemyHpBar = { 417, 301, enemyHpMaxWidth, 10 };
	playerHpBar = { 895, 648, playerHpMaxWidth, 10 };

	winningQuotes = { "Dammit you defeated me! gl on your journey", "WHAT HOW?! i better go train..", "Here take my money $" + std::to_string(dynamic_cast<Trainer*>(enemy)->GetMoney()), "Wow! you're really good! gl" };
	losingQuotes = { "You're not strong enough for me!", "Go train so you can get stronger", "That was easy..", "Next..." };
}

void BattleTrainer::SetupBattle()
{
	if (dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon() == nullptr)
	{
		state = BattleState::End;
		iWon = true;
	}
	else if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon() == nullptr)
	{
		state = BattleState::End;
		iWon = false;
	}

	if (state != BattleState::End)
	{
		bHud.DrawBattleFrame();


		if (state != BattleState::Start)
		{
			bHud.DrawPlayerPokemonEntrance(dynamic_cast<Trainer*>(player)->GetInBattlePokemon());
			bHud.DrawEnemyTrainerPokemonEntrance(dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon());
			bHud.DrawPokemonBar(dynamic_cast<Trainer*>(player)->GetInBattlePokemon(), dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon());
			bHud.DrawHealthBar(playerHpBar);
			bHud.DrawHealthBar(enemyHpBar);

			enemyHpBar.w = (dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetStats().MaxHP;
			playerHpBar.w = (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetStats().MaxHP;
		}
	}

}

void BattleTrainer::Update()
{
	/*if (state == BattleState::EnemyMove)
		t = new std::thread(([this] {this->HandleEnemyAction(); }));*/
	SetupBattle();


	switch (state)
	{
	case BattleState::Start:
		message = "You think you can defeat me?";
		bHud.DrawTrainerEntrance(player);
		bHud.DrawEnemyTrainerEntrance(enemy);
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
		PlayerMove();
		HandleMoveSelection();
		PerformPlayerAttack();
		break;
	case BattleState::EnemyMove:
		PerformEnemyAttack();
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
	case BattleState::Busy:
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

void BattleTrainer::PerformPlayerAttack()
{
	if (Input::KeyPressed(Key::RETURN))
	{
		if (IGoFirst())
		{
			dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->TakeDamage(dynamic_cast<Trainer*>(player)->GetInBattlePokemon(), currentMove);
			message = dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetName() + " Used " + dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetMoveAt(currentMove)->GetMoveName();
			if (dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetHP() < 0)
				dynamic_cast<Trainer*>(enemy)->SetInBattlePokemon(GetEnemyNextHealthyPokemon());
			else
				state = BattleState::EnemyMove;
		}
		else
			state = BattleState::EnemyMove;
	}
}

void BattleTrainer::PerformEnemyAttack()
{
	if (timer != 20)
	{
		timer++;
	}
	else
	{
		srand(time(0));
		int randMove = rand() % dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetMoves().size();
		dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->TakeDamage(dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon(), PrioritiesEnemyMove(dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()));
		message = dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetName() + " Used " + dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetMoveAt(PrioritiesEnemyMove(dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()))->GetMoveName();
		if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetHP() < 0)
		{
			message = dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetName() + " Fainted!";
			state = BattleState::Death;
			//player->SetInBattlePokemon(GetNextHealthyPokemon());
		}
		else
			state = BattleState::PlayerAction;

		timer = 0;
	}
}

bool BattleTrainer::IGoFirst()
{
	if (dynamic_cast<Trainer*>(player)->GetInBattlePokemon()->GetStats().Speed >= dynamic_cast<Trainer*>(enemy)->GetInBattlePokemon()->GetStats().Speed)
		return true;
	return false;
}

void BattleTrainer::EndBattle()
{
	if (iWon && !end)
	{
		message = winningQuotes[RandNum(0, winningQuotes.size() - 1)];
		end = true;
	}
	else if (!iWon && !end)
	{
		message = losingQuotes[RandNum(0, losingQuotes.size() - 1)];
		end = true;
	}
}


Pokemon* BattleTrainer::GetEnemyNextHealthyPokemon()
{
	for (int i = 0; i < 4; i++)
	{
		if (dynamic_cast<Trainer*>(enemy)->GetPokemonAtIndex(i) != nullptr && dynamic_cast<Trainer*>(enemy)->GetPokemonAtIndex(i)->GetHP() > 0)
			return dynamic_cast<Trainer*>(enemy)->GetPokemonAtIndex(i);
	}
	return nullptr;
}
