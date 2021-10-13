#include "NpcController.h"
#include "Trainer.h"
#include "../Battle/BattleTrainer.h"


void NpcController::Update(Character* character, Character* player)
{
	character->SetSpeed(2);
	if (character->GetMovePattern().size() > 0)
	{
		if (state == NpcState::Idle)
		{
			idleTimer++;
			if (idleTimer > timeBetweenWalking)
			{
				if (currentPattern < character->GetMovePattern().size())
				{
					timer += character->GetSpeed();
					if (timer <= 64)
					{
						character->Move(character->GetMovePattern()[currentPattern]);
						character->SetIsWalking(true);
						character->Animate(character->GetMovePattern()[currentPattern].direction, 4);
					}
					else
					{
						//idleTimer = 0;
						timer = 0;
					}
					//std::cout << character->GetXPos() / 64 << ", " << character->GetMovePattern()[currentPattern].vector2.x << "\n";
					if ((character->GetXPos() / 64 == character->GetMovePattern()[currentPattern].vector2.x))
					{
						currentPattern = (currentPattern + 1) % character->GetMovePattern().size();
						idleTimer = 0;
					}
					else if ((character->GetYPos() / 64 == character->GetMovePattern()[currentPattern].vector2.y))
					{
						currentPattern = (currentPattern + 1) % character->GetMovePattern().size();
						idleTimer = 0;
					}
				}
				else
					movePatternIsDone = true;
			}
			else
				character->SetIsWalking(false);
		}
	}
}

bool NpcController::TrainerInSight(Character* character, Character* player)
{
	if (character->GetIsTrainer())
		if (Collision::XYInRect(dynamic_cast<Trainer*>(character)->GetViewRect(), player->GetCollisionPoint().x, player->GetCollisionPoint().y) && !dynamic_cast<Trainer*>(player)->GetIsInTrainerBattle())
		{
			if (!dynamic_cast<Trainer*>(character)->GetIsDefeated())
			{
				dynamic_cast<Trainer*>(player)->SetIsSpottet(true);
				//battle = new BattleTrainer(player, character);
				//dynamic_cast<Trainer*>(player)->SetIsInBattle(true);
				return true;
			}
		}
	return false;
}

void NpcController::StartEncounter(Character* character, Character* player, DialogManager* dialog)
{
	if (!encounterStarted)
	{
		character->AddToMovePattern(NpcPattern(Vector2(character->GetCollisionPoint().x - player->GetCollisionPoint().x, character->GetCollisionPoint().y - player->GetCollisionPoint().y), AnimationDirection::DOWN));
		encounterStarted = true;
		player->SetCanWalk(false);
	}
	if (Collision::AABB(character->GetCollisionPoint(), player->GetPosition()) && !encountered)
		//if (npcController.movePatternIsDone && !encountered)
	{
		character->ClearPath();
		dialog->SetIsActive(true);
		encountered = true;
	}
	else if (encountered)
	{
		if (!dialog->GetIsActive());
			battle = new BattleTrainer(player, character);
		static_cast<Trainer*>(player)->SetIsInTrainerBattle(true);
	}
}

void NpcController::StartDefaultEncounter(Character* character, Character* player, DialogManager* dialog)
{
	if (!dialog->GetIsActive() && !defaultStarted)
	{
		battle = new BattleTrainer(player, character);
		defaultStarted = true;
	}
}
