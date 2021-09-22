#include "GameController.h"
#include "Core/Collision.h"
#include <iostream>
#include "Battle/BattleTrainer.h"

GameController::GameController()
{
	scene = new Scene();
	scene->LoadNewScene(new PalletTown(scene->GetPlayer(), 31, 31, 32, 1, 2));
	scene->GetPlayer()->SetXYPosition(5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom(), 5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom());
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
		WalkInDoor();
		break;
	case GameState::Battle:
		npcController.GetBattleSystem()->Update();
		break;
	case GameState::Dialog:
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
	scene->GetMap()->Collision();
	scene->GetMap()->SetNpcTile();
	for (int i = 0; i < scene->GetMap()->GetNpcs().size(); i++)
	{
		scene->GetMap()->GetNpcs()[i]->UpdateCharacter(elapsedTime);

		if (!Collision::AABB(scene->GetPlayer()->GetPosition(), scene->GetMap()->GetNpcs()[i]->GetInteractPoint()))
			npcController.Update(scene->GetMap()->GetNpcs()[i], scene->GetPlayer());
		else
			scene->GetMap()->GetNpcs()[i]->SetIsWalking(false);
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
	else if (!dialogManager->GetIsActive())
		state = GameState::Free;

	if (dynamic_cast<Trainer*>(scene->GetPlayer())->GetIsInBattle())
		state = GameState::Battle;
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
