#include "GameController.h"
#include "Core/Collision.h"
#include <iostream>
#include "Battle/BattleTrainer.h"

GameController::GameController()
{
	scene = new Scene();
	scene->LoadNewScene(new PalletTown(scene->GetPlayer(), 31, 31, 32, 1, 2));
	scene->GetPlayer()->SetXYPosition(5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom() - 5, 11 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom() - 8);
	//scene->GetPlayer()->SetXYPosition(0, 0);
	dialogManager = new DialogManager();
	controller = new PlayerController(scene->GetPlayer(), scene->GetMap());
}

GameController::~GameController()
{
	
}

void GameController::Update(float elapsedTime)
{
	ConstantUpdate(elapsedTime);

	switch (state)
	{
	case GameState::Free:
		controller->Update(elapsedTime);
		StartBattle();
		WalkInDoor();
		scene->GetPlayer()->SetCanWalk(true);
		break;
	case GameState::TrainerBattle:
		npcController.GetBattleSystem()->Update();
		break;
	case GameState::PokemonBattle:
		controller->GetBattle()->Update();
		break;
	case GameState::Encounter:
		break;
	case GameState::Dialog:
		if (scene->GetMap()->GetCollidedNpc() == nullptr)
			dialogManager->ShowDialog(scene->GetPlayer()->GetDialog());
		else
			dialogManager->ShowDialog(scene->GetMap()->GetCollidedNpc()->GetDialog());
		break;
	default:
		break;
	}
}

void GameController::ConstantUpdate(float elapsedTime)
{
	scene->Update();
	scene->GetPlayer()->UpdateCharacter(elapsedTime);
	scene->GetMap()->GetCamera()->Update();
	scene->GetMap()->SetNpcTile();
	ReturnToLastCheckpoint();
	for (int i = 0; i < scene->GetMap()->GetNpcs().size(); i++)
	{
		scene->GetMap()->GetNpcs()[i]->UpdateCharacter(elapsedTime);

		if (!Collision::AABB(scene->GetPlayer()->GetPosition(), scene->GetMap()->GetNpcs()[i]->GetCollisionPoint()))
			npcController.Update(scene->GetMap()->GetNpcs()[i], scene->GetPlayer());
		else
			scene->GetMap()->GetNpcs()[i]->SetIsWalking(false);

		if (npcController.TrainerInSight(scene->GetMap()->GetNpcs()[i], scene->GetPlayer()) && !static_cast<Trainer*>(scene->GetPlayer())->GetIsSpottet());
		{
			//scene->GetMap()->SetCollidedNpc(scene->GetMap()->GetNpcs()[i]);
		}
	}
	//for (int i = 0; i < scene->GetMap()->GetNpcs().size(); i++)
	//	if (!Collision::AABB(scene->GetPlayer()->GetPosition(), scene->GetMap()->GetNpcs()[i]->GetInteractPoint()))
	//		npcController.Update(scene->GetMap()->GetNpcs()[i], scene->GetPlayer());
	//	else
	//		scene->GetMap()->GetNpcs()[i]->SetIsWalking(false);



	if (dialogManager->GetIsActive())
	{
		state = GameState::Dialog;
	}
	else
		state = GameState::Free;

	if (dynamic_cast<Trainer*>(scene->GetPlayer())->GetIsInTrainerBattle())
		state = GameState::TrainerBattle;

	if (dynamic_cast<Trainer*>(scene->GetPlayer())->GetIsInPokemonBattle())
		state = GameState::PokemonBattle;


	if (dynamic_cast<Trainer*>(scene->GetPlayer())->GetIsSpottet() && state != GameState::Dialog && state != GameState::TrainerBattle)
	{
		scene->GetDraw().DrawExclamationmark(scene->GetMap()->GetCollidedNpc());
		npcController.StartEncounter(scene->GetMap()->GetCollidedNpc(), scene->GetPlayer(), dialogManager);
	}
	//else
	//	state = GameState::Free;
}

void GameController::WalkInDoor()
{
	if (scene->GetMap()->LoadNewMap() != nullptr)
	{
		scene->LoadNewScene(scene->GetMap()->LoadNewMap());
		delete controller;
		controller = new PlayerController(scene->GetPlayer(), scene->GetMap());
	}
}

void GameController::CheckForInteraction()
{
	
}

void GameController::StartBattle()
{
	for (int i = 0; i < scene->GetMap()->GetNpcs().size(); i++)
	{
		if (npcController.TrainerInSight(scene->GetMap()->GetNpcs()[i], scene->GetPlayer()))
		{
			
			//if (scene->GetMap()->GetNpcs()[i]->GetXPos() )

		}

	}
}

void GameController::ReturnToLastCheckpoint()
{
	if (dynamic_cast<Trainer*>(scene->GetPlayer())->IsWholeTeamDead() && state == GameState::Free)
	{
		for (int i = 0; i < dynamic_cast<Trainer*>(scene->GetPlayer())->GetSizeOfPokebag(); i++)
		{
			dynamic_cast<Trainer*>(scene->GetPlayer())->GetPokemonAtIndex(i)->RefreshHP();
		}
		//scene->GetCheckpoint().InitCheckpoints(scene->GetPlayer());
		/*scene->LoadNewScene(scene->GetCheckpoint()->currentCheckpoint);
		delete controller;
		controller = new PlayerController(scene->GetPlayer(), scene->GetMap());*/
		//dynamic_cast<Trainer*>(scene->GetPlayer())->SetXYPosition(scene->GetCheckpoint().GetPosition()->x, scene->GetCheckpoint().GetPosition()->y);
		//scene->GetPlayer()->SetXYPosition(scene->GetCheckpoint()->GetPosition()->x * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom(), scene->GetCheckpoint()->GetPosition()->y * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom());
		//scene->GetCheckpoint()->NullifyCheckpoint();
	}
}
