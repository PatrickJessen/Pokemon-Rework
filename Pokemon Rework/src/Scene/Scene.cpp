#include "Scene.h"

Scene::Scene()
{
	draw = new Draw();
	player = new Trainer("Ash", "Assets/Characters/Ash.png", "Assets/Characters/AshBack.png", 75, 75, 100);
}

Scene::~Scene()
{
	delete current;
}

void Scene::Update()
{
	draw->Update(current, player);
}

void Scene::LoadNewScene(Map* map)
{
	delete current;
	current = map;
	current->InitMap();
	current->GetCamera()->SetTarget(&player->GetPosition());
}
