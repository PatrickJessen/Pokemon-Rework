#include "PalletTown.h"
#include "OakLab.h"
#include "../../../../Dialog/DialogManager.h"

PalletTown::PalletTown(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	containsCheckpoint = true;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 50);

	filePath = "Assets/Map/Pallet Town/TileType/PTown.map";
	texturePath = "Assets/Map/Pallet Town/PTown.png";
	imagePath = "Assets/Map/Pallet Town/PTownSprites.map";

	doors.emplace(1, std::vector<Vector2> { Vector2(0, 11), Vector2(0, 12), Vector2(0, 13)
		, Vector2(0, 14), Vector2(0, 15), Vector2(0, 16), Vector2(0, 17) });

	doors.emplace(0, std::vector<Vector2> { Vector2(18, 23) });

	dynamic_cast<Trainer*>(player)->AddPokemonToBag(new Charmander(5));
	dynamic_cast<Trainer*>(player)->GetPokemonAtIndex(0)->OnPokemonCreate();
	std::cout << dynamic_cast<Trainer*>(player)->GetPokemonAtIndex(0)->GetStats().MaxHP << "\n";

	/*npcs.push_back(new Npc("Shit", "Assets/Trainers/Gary.png", 70, 70, 62, 65));
	npcs[0]->SetXYPosition(10 * tileSize * camera->GetZoom() - 5, 5 * tileSize * camera->GetZoom() - 9);*/
	//npcs.push_back(new Trainer("Trainer", "Assets/Trainers/Gary.png", "Assets/Characters/garyFront.png", 70, 70, 62, 65, 500));
	//npcs[1]->SetXYPosition(10 * tileSize * camera->GetZoom() - 5, 10 * tileSize * camera->GetZoom() - 9);
	//npcs[1]->AddDialog("You think you can defeat me?");
	//static_cast<Trainer*>(npcs[1])->AddPokemonToBag(new Bulbasaur(5));

	//std::cout << static_cast<Trainer*>(npcs[1])->GetPokemonAtIndex(0)->name << "\n";
	/*npcs[0]->AddDialog("Have you visited Oak's lab?");
	npcs[0]->AddDialog("You can get your first pokemon there");*/
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom * 2, 0), AnimationDirection::RIGHT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom * -2, 0), AnimationDirection::LEFT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(0, npcs[0]->GetXPos() / tileSize / zoom + -4), AnimationDirection::UP));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom + 4, 0), AnimationDirection::RIGHT));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(0, npcs[0]->GetXPos() / tileSize / zoom + 4), AnimationDirection::DOWN));
	//npcs[0]->AddToMovePattern(NpcPattern(Vector2(npcs[0]->GetXPos() / tileSize / zoom + -4, 0), AnimationDirection::LEFT));

	checkpoint = new Vector2(6 * tileSize * zoom - 5, 12 * tileSize * zoom - 8);
	lastCheckpoint = this;
	lastCheckpoint->checkpoint = new Vector2(6 * tileSize * zoom - 5, 12 * tileSize * zoom - 8);


	if (static_cast<Trainer*>(player)->GetStarterPoke() != nullptr && !player->GetQuestByNumber(2)->GetIsFinnished())
	{
		npcs.push_back(new Trainer("Gary", "Assets/Trainers/Gary.png", "Assets/Characters/garyFront.png", 70, 70, 62, 65, 500));
		GetCharacterByName("Gary")->SetVisibility(false);

		GetCharacterByName("Gary")->SetXYPosition(18 * tileSize * camera->GetZoom() - 5, 18 * tileSize * camera->GetZoom() - 9);

		if (static_cast<Trainer*>(player)->GetStarterPoke()->GetType() == Type::FIRE)
			dynamic_cast<Trainer*>(GetCharacterByName("Gary"))->AddPokemonToBag(new Squirtle(2));

		else if (static_cast<Trainer*>(player)->GetStarterPoke()->GetType() == Type::WATER)
			dynamic_cast<Trainer*>(GetCharacterByName("Gary"))->AddPokemonToBag(new Bulbasaur(5));

		else if (static_cast<Trainer*>(player)->GetStarterPoke()->GetType() == Type::GRASS)
			dynamic_cast<Trainer*>(GetCharacterByName("Gary"))->AddPokemonToBag(new Charmander(5));

		dynamic_cast<Trainer*>(GetCharacterByName("Gary"))->GetPokemonAtIndex(0)->OnPokemonCreate();
	}
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
		//oakLab = new OakLab(trainer, camera, 1, 27, 27, 32);
		player->SetXYPosition(14 * tileSize - 5, 22 * tileSize - 8);
		return new OakLab(player, 27, 27, 32, 0, 1);
	}
	break;
	case 1:
	{
		/*if (player->GetQuestByNumber(1)->GetIsFinnished())
		{
			route1 = new Route1(player, 51, 51, 32, 2, 2);
			player->SetXYPosition(14 * tileSize * camera->GetZoom() - 5, 48 * tileSize * camera->GetZoom() - 8);
			return route1;
		}
		else
		{
			player->AddDialog("I better go visit proffesor Oak. before going out in the wild");
			DialogManager::GetInstance()->SetIsActive(true);
			player->SetYPos((player->GetYPos() / tileSize / camera->GetZoom()) + 100);
			player->Animate(AnimationDirection::DOWN, 1);
		}*/

			route1 = new Route1(player, 51, 51, 32, 2, 2);
		player->SetXYPosition(14 * tileSize * camera->GetZoom() - 5, 48 * tileSize * camera->GetZoom() - 8);
		return route1;
	}
	break;
	}
	return nullptr;
}

Map* PalletTown::SpawnAtCheckpoint()
{
	return lastCheckpoint;
}

void PalletTown::Update()
{
	if (!DialogManager::GetInstance()->GetIsActive())
		player->ClearDialog();
	if (player->GetTileY(tileSize, camera->GetZoom()) <= 5 && static_cast<Trainer*>(player)->GetStarterPoke() != nullptr && !player->GetQuestByNumber(2)->GetIsFinnished())
		EncounterGary();
}
void PalletTown::EncounterGary()
{
	GetCharacterByName("Gary")->SetVisibility(true);
	camera->SetTarget(&GetCharacterByName("Gary")->GetCollisionPoint());
	//GetCharacterByName("Gary")->MoveTowardsPlayer(static_cast<Trainer*>(player), tileSize, camera->GetZoom());
	if (GetCharacterByName("Gary")->MoveTowardsPlayer(static_cast<Trainer*>(player), tileSize, camera->GetZoom()) && !isDoneMoving)
	{
		camera->SetTarget(&player->GetPosition());
		SetCollidedNpc(GetCharacterByName("Gary"));
		dynamic_cast<Trainer*>(player)->SetIsInTrainerBattle(true);
		isDoneMoving = true;
		player->GetQuestByNumber(2)->SetIsFinnished(true);
	}
}
