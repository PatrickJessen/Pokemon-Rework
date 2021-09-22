#include "PalletTown.h"

PalletTown::PalletTown(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 50);

	filePath = "Assets/Map/Pallet Town/TileType/PTown.map";
	texturePath = "Assets/Map/Pallet Town/PTown.png";
	imagePath = "Assets/Map/Pallet Town/PTownSprites.map";

	doors.emplace(1, std::vector<Vector2> { Vector2(0, 11), Vector2(0, 12), Vector2(0, 13)
		, Vector2(0, 14), Vector2(0, 15), Vector2(0, 16), Vector2(0, 17) });

	npcs.push_back(new Npc("Shit", "Assets/Trainers/Gary.png", 75, 75, 62, 65));
	npcs.push_back(new Trainer("Trainer", "Assets/Trainers/Gary.png", "Assets/Characters/garyFront.png", 75, 75, 62, 65, 500));
	npcs[1]->SetXYPosition(10 * tileSize * camera->GetZoom(), 10 * tileSize * camera->GetZoom());
	npcs[1]->AddDialog("You think you can defeat me?");
	static_cast<Trainer*>(npcs[1])->AddPokemonToBag(new Bulbasaur(5));
	static_cast<Trainer*>(player)->AddPokemonToBag(new Charmander(5));
	static_cast<Trainer*>(player)->GetPokemonAtIndex(0)->OnPokemonCreate();
	static_cast<Trainer*>(npcs[1])->GetPokemonAtIndex(0)->OnPokemonCreate();
	std::cout << static_cast<Trainer*>(player)->GetPokemonAtIndex(0)->name << "\n";
	std::cout << static_cast<Trainer*>(npcs[1])->GetPokemonAtIndex(0)->name << "\n";
	npcs[0]->SetXYPosition(10 * tileSize * camera->GetZoom(), 5 * tileSize * camera->GetZoom());
	npcs[0]->AddDialog("Have you visited Oak's lab?");
	npcs[0]->AddDialog("You can get your first pokemon there");
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom * 2, 0), AnimationDirection::RIGHT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom * -2, 0), AnimationDirection::LEFT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(0, npcs[0]->GetXPos() / tileSize / zoom + -4), AnimationDirection::UP));
	npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom + 4, 0), AnimationDirection::RIGHT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(0, npcs[0]->GetXPos() / tileSize / zoom + 4), AnimationDirection::DOWN));
	npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom + -4, 0), AnimationDirection::LEFT));
}

PalletTown::~PalletTown()
{
	
}

Map* PalletTown::LoadNewMap()
{
	int x = EnterDoor(camera->GetCamera().x, camera->GetCamera().y);
	switch (x)
	{
	case 0:
	{
		//trainer->GetCollisionPoint() = { trainer->GetXPos() + trainer->GetWidth() / 2, trainer->GetYPos() + trainer->GetHeight() / 2 + 5, 10, 10 };
		/*oakLab = new OakLab(trainer, camera, 1, 27, 27, 32);
		return oakLab;*/
	}
	break;
	case 1:
	{
		//if (trainer->Quests[1]->completed)
		{
			route1 = new Route1(player, 51, 51, 32, 2, 2);
			player->SetXYPosition(14 * tileSize * camera->GetZoom(), 48 * tileSize * camera->GetZoom());
			return route1;
		}
	}
	break;
	}
	return nullptr;
}
