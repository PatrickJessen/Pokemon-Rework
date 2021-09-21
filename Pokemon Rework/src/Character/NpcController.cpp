#include "NpcController.h"
#include "Trainer.h"


void NpcController::Update(Character* character, Character* player)
{
	if (character->GetMovePattern().size() > 0)
	{
		if (state == NpcState::Idle)
		{
			idleTimer++;
			if (idleTimer > timeBetweenWalking)
			{
				character->Move(character->GetMovePattern()[currentPattern]);
				character->SetIsWalking(true);
				character->Animate(character->GetMovePattern()[currentPattern].direction, 4);
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
				//else if (character->GetYPos() / 64 == (character->GetYPos() / 64) + character->GetMovePattern()[currentPattern].vector2.y)
				//{
				//	std::cout << character->GetYPos() + character->GetMovePattern()[currentPattern].vector2.y << "\n";
				//	//currentPattern = (currentPattern + 1) % character->GetMovePattern().size();
				//	currentPattern = (currentPattern + 1) % character->GetMovePattern().size();
				//	isWalking = true;
				//	idleTimer = 0;
				//}
			}
			else
				character->SetIsWalking(false);
		}
	}

	TrainerInSight(character, player);
}

void NpcController::TrainerInSight(Character* character, Character* player)
{
	if (character->GetIsTrainer())
		if (Collision::XYInRect(dynamic_cast<Trainer*>(character)->GetViewRect(), player->GetPosition().x, player->GetPosition().y))
		{
			if (!dynamic_cast<Trainer*>(character)->GetIsDefeated())
				dynamic_cast<Trainer*>(player)->SetIsInBattle(true);
		}
}
