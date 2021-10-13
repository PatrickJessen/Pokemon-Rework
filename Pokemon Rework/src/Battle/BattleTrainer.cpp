#include "BattleTrainer.h"
#include <future>

BattleTrainer::BattleTrainer(Character* player, Character* enemy)
{
	this->player = static_cast<Trainer*>(player);
	this->enemy = static_cast<Trainer*>(enemy);
	bHud.SetData();
	this->enemy->SetInBattlePokemon(GetEnemyNextHealthyPokemon());
	this->player->SetInBattlePokemon(GetNextHealthyPokemon());
	playerHpMaxWidth = 175;
	enemyHpMaxWidth = 175;
	expBarMaxWidth = 175;
	enemyHpBar = { 417, 301, enemyHpMaxWidth, 10 };
	playerHpBar = { 895, 648, playerHpMaxWidth, 10 };
	expBar = { 895, 630, expBarMaxWidth, 10 };

	winningQuotes = { "Dammit you defeated me! gl on your journey", "WHAT HOW?! i better go train..", "Here take my money $" + std::to_string(this->enemy->GetMoney()), "Wow! you're really good! gl" };
	losingQuotes = { "You're not strong enough for me!", "Go train so you can get stronger", "That was easy..", "Next..." };
}

void BattleTrainer::SetupBattle()
{
	if (enemy->GetInBattlePokemon() == nullptr)
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

void BattleTrainer::Update()
{
	dialog.ShowDialog(message);
	/*if (state == BattleState::EnemyMove)
		t = new std::thread(([this] {this->HandleEnemyAction(); }));*/
	SetupBattle();

	if (state != BattleState::End)
	{
		bHud.DrawBattleFrame();


		if (state != BattleState::Start)
		{
			bHud.DrawPlayerPokemonEntrance(player->GetInBattlePokemon());
			bHud.DrawEnemyTrainerPokemonEntrance(enemy->GetInBattlePokemon());
			bHud.DrawPokemonBar(player->GetInBattlePokemon(), enemy->GetInBattlePokemon());
			bHud.DrawHealthBar(playerHpBar);
			bHud.DrawHealthBar(enemyHpBar);
			bHud.DrawExpBar(expBar);

			enemyHpBar.w = (enemy->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / enemy->GetInBattlePokemon()->GetStats().MaxHP;
			playerHpBar.w = (player->GetInBattlePokemon()->GetHP() * enemyHpMaxWidth) / player->GetInBattlePokemon()->GetStats().MaxHP;
			expBar.w = (player->GetInBattlePokemon()->GetExp() * expBarMaxWidth) / player->GetInBattlePokemon()->GetRequiredExp(); // / max exp
			
		}
	}

	switch (state)
	{
	case BattleState::Start:
		message = "";
		bHud.DrawTrainerEntrance(player);
		bHud.DrawEnemyTrainerEntrance(enemy);
		if (Input::KeyPressed(Key::SPACE))
		{
			state = BattleState::PlayerAction;
			message = "Go " + player->GetInBattlePokemon()->GetName() + "!";
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
		if (hit == true)
			t1.join();
		if (IGoFirst())
		{
			enemy->GetInBattlePokemon()->TakeDamage(player->GetInBattlePokemon(), currentMove);
			message = player->GetInBattlePokemon()->GetName() + " Used " + player->GetInBattlePokemon()->GetMoveAt(currentMove)->GetMoveName();
			if (enemy->GetInBattlePokemon()->GetHP() < 0)
			{
				int enemyLevel = enemy->GetInBattlePokemon()->GetLevel();

				int expGain = (enemyLevel * 1.5f) / 7;

				player->GetInBattlePokemon()->SetExp(expGain);
				std::this_thread::sleep_for(std::chrono::seconds(2));
				enemy->SetInBattlePokemon(GetEnemyNextHealthyPokemon());
			}
			else
			{
				state = BattleState::EnemyMove;
				t1 = std::thread(&BattleTrainer::PerformEnemyAttack, this);
			}
		}
		else
		{
			state = BattleState::EnemyMove;
			t1 = std::thread(&BattleTrainer::PerformEnemyAttack, this);
		}


	}
}

void BattleTrainer::PerformEnemyAttack()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	player->GetInBattlePokemon()->TakeDamage(enemy->GetInBattlePokemon(), PrioritiesEnemyMove(enemy->GetInBattlePokemon()));
	message = enemy->GetInBattlePokemon()->GetName() + " Used " + enemy->GetInBattlePokemon()->GetMoveAt(PrioritiesEnemyMove(enemy->GetInBattlePokemon()))->GetMoveName();
	if (player->GetInBattlePokemon()->GetHP() < 0)
	{
		message = player->GetInBattlePokemon()->GetName() + " Fainted!";
		state = BattleState::Death;
		//player->SetInBattlePokemon(GetNextHealthyPokemon());
	}
	else
		state = BattleState::PlayerAction;

	hit = true;
}

bool BattleTrainer::IGoFirst()
{
	if (player->GetInBattlePokemon()->GetStats().Speed >= enemy->GetInBattlePokemon()->GetStats().Speed)
		return true;
	return false;
}

void BattleTrainer::EndBattle()
{
	if (iWon && !end)
	{
		message = winningQuotes[RandNum(0, winningQuotes.size() - 1)];
		end = true;
		enemy->SetIsDefeated(true);
		enemy->ClearDialog();
		enemy->AddDialog("I will train harder for our next battle!");
	}
	else if (!iWon && !end)
	{
		message = losingQuotes[RandNum(0, losingQuotes.size() - 1)];
		end = true;
	}

	if (Input::KeyPressed(Key::SPACE))
	{
		player->SetIsInTrainerBattle(false);
		player->SetIsSpottet(false);
	}
}


Pokemon* BattleTrainer::GetEnemyNextHealthyPokemon()
{
	for (int i = 0; i < 4; i++)
	{
		if (enemy->GetPokemonAtIndex(i) != nullptr && enemy->GetPokemonAtIndex(i)->GetHP() > 0)
			return enemy->GetPokemonAtIndex(i);
	}
	return nullptr;
}
