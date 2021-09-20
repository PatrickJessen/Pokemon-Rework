#include "GameController.h"
#include "Core/Collision.h"

GameController::GameController()
{
	scene = new Scene();
	scene->LoadNewScene(new PalletTown(scene->GetPlayer(), 31, 31, 32, 1, 2));
	scene->GetPlayer()->SetXYPosition(5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom(), 5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom());
	//scene->GetPlayer()->SetXYPosition(0, 0);
	dialogManager = new DialogManager();
	controller = new PlayerController(scene->GetPlayer(), scene->GetMap(), dialogManager);
}

GameController::~GameController()
{
}

void GameController::Update()
{
	ConstantUpdate();

	switch (state)
	{
	case GameState::Free:
		controller->Update();
		WalkInDoor();
		break;
	case GameState::Battle:
		break;
	case GameState::Dialog:
		dialogManager->ShowDialog(scene->GetMap()->GetCollidedNpc()->dialog);
		break;
	default:
		break;
	}
}

void GameController::ConstantUpdate()
{
	scene->Update();
	scene->GetPlayer()->Update();
	scene->GetMap()->GetCamera()->Update();
	for (int i = 0; i < scene->GetMap()->GetNpcs().size(); i++)
	{
		scene->GetMap()->GetNpcs()[i]->Update();
	}

	if (dialogManager->GetIsActive())
	{
		state = GameState::Dialog;
	}
	else if (!dialogManager->GetIsActive())
		state = GameState::Free;
}

void GameController::WalkInDoor()
{
	if (scene->GetMap()->LoadNewMap() != nullptr)
	{
		scene->LoadNewScene(scene->GetMap()->LoadNewMap());
		delete controller;
		controller = new PlayerController(scene->GetPlayer(), scene->GetMap(), dialogManager);
	}
}

void GameController::CheckForInteraction()
{
	
}
