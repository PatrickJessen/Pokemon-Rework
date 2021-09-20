#include "GameController.h"

GameController::GameController()
{
	scene = new Scene();
	scene->LoadNewScene(new PalletTown(scene->GetPlayer(), 31, 31, 32, 1, 2));
	scene->GetMap()->GetCamera()->SetTarget(&scene->GetPlayer()->GetPosition());
	scene->GetPlayer()->SetXYPosition(5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom(), 5 * scene->GetMap()->GetTileSize() * scene->GetMap()->GetCamera()->GetZoom());
	//scene->GetPlayer()->SetXYPosition(0, 0);
	controller = new PlayerController(scene->GetPlayer(), scene->GetMap());
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
}

void GameController::WalkInDoor()
{
	/*if (scene->GetMap()->LoadNewMap() != nullptr)
	{
		scene->LoadNewScene(scene->GetMap()->LoadNewMap());
		scene->GetMap()->GetCamera()->SetTarget(&scene->GetPlayer()->GetPosition());
		delete controller;
		controller = new PlayerController(scene->GetPlayer(), scene->GetMap());
	}*/
}
