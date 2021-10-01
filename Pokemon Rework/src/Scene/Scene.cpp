#include "Scene.h"

Scene::Scene()
{
	player = new Trainer("Ash", "Assets/Characters/Ash.png", "Assets/Characters/AshBack.png", 75, 75, 62, 65, 100);
	checkpoint = new Checkpoint();
	checkpoint->InitCheckpoints(player);
}

Scene::~Scene()
{
	delete current;
}

void Scene::Update()
{
	draw.Update(current, player);
	checkpoint->SetCurrentCheckpoint(GetMap()->GetCamera());
	//std::cout << (Map*)lastCheckpoint->x << "\n";
}

void Scene::LoadNewScene(Map* map)
{
	delete current;
	current = map;
	current->InitMap();
	current->GetCamera()->SetTarget(&player->GetPosition());
	//checkpoint->NullifyCheckpoint();
}

void Scene::SetNewCheckpoint()
{
}

Map* Scene::GetLastCheckpoint()
{
	return lastCheckpoint;
}
