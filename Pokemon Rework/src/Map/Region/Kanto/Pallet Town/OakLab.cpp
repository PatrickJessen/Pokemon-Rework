#include "OakLab.h"
#include "PalletTown.h"
#include "../../../../Dialog/DialogManager.h"

OakLab::OakLab(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	containsCheckpoint = false;
	camera = new Camera(zoom);

	filePath = "Assets/Map/Pallet Town/Oak Lab/OaklabTiles.map";
	texturePath = "Assets/Map/Pallet Town/Oak Lab/Oaklab.png";
	imagePath = "Assets/Map/Pallet Town/Oak Lab/OaklabSprites.map";

	pokemon = new Sprite("Nihility", SDL_ScaleMode::SDL_ScaleModeBest);
	pokeballs = new Sprite("Assets/Items/Pokeball.png", SDL_ScaleMode::SDL_ScaleModeBest);

	camera->SetZoom(1);
	camera->SetFollowPlayer(false);
	camera->SetOptions(tileSize, height, 0);
	ballRect1 = { 1030, 490, 50, 50 };
	ballRect2 = { 1100, 490, 50, 50 };
	ballRect3 = { 1170, 490, 50, 50 };

	ballInteractRect1 = { 1030, 560, 20, 10 };
	ballInteractRect2 = { 1100, 560, 20, 10 };
	ballInteractRect3 = { 1170, 560, 20, 10 };


	doors.emplace(0, std::vector<Vector2> { Vector2(25, 14), Vector2(25, 13), Vector2(25, 15) });

	npcs.push_back(new Npc("Prof. Oak", "Assets/Characters/ProOak.png", 70, 70, 60, 60));
	GetCharacterByName("Prof. Oak")->SetSrcRect(0, 73, 50, 55);
	GetCharacterByName("Prof. Oak")->SetXYPosition(10 * tileSize - 5, 10 * tileSize - 8);
	GetCharacterByName("Prof. Oak")->AddDialog("Choose your first pokemon wisely");
	//player->SetInteractPoint(player->GetYPos() + width / 2, player->GetXPos() + height / 2 + 5, 10, 10);
}

OakLab::~OakLab()
{
}

Map* OakLab::LoadNewMap()
{
	int x = EnterDoor(camera->GetCamera().x, camera->GetCamera().y);
	switch (x)
	{
	case 0:
	{
		//trainer->GetCollisionPoint() = { trainer->GetXPos() + trainer->GetWidth() / 2, trainer->GetYPos() + trainer->GetHeight() / 2 + 5, 10, 10 };
		//oakLab = new OakLab(trainer, camera, 1, 27, 27, 32);
		player->SetXYPosition(19 * tileSize * camera->GetZoom() - 5, 23 * tileSize * camera->GetZoom() - 8);
		return new PalletTown(player, 31, 31, 32, 1, 2);
	}
	break;
	}
	return nullptr;
}

void OakLab::Update()
{
	PlacePokeballs();
	InteractWithPokeball();
	InteractWithOak();
	player->GetInteractPoint().x -= camera->GetCamera().x;
	player->GetInteractPoint().y -= camera->GetCamera().y;

	if (GetCharacterByName("Prof. Oak")->GetDialog().Lines.size() == 0)
		GetCharacterByName("Prof. Oak")->AddDialog("Choose your first pokemon wisely");
}

void OakLab::PlacePokeballs()
{
	if (dynamic_cast<Trainer*>(player)->GetStarterPoke() != nullptr && dynamic_cast<Trainer*>(player)->GetStarterPoke()->GetName() == "Charmander")
	{
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect1);
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect2);
	}
	else if (dynamic_cast<Trainer*>(player)->GetStarterPoke() != nullptr && dynamic_cast<Trainer*>(player)->GetStarterPoke()->GetName() == "Squirtle")
	{
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect1);
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect3);
	}
	else if (dynamic_cast<Trainer*>(player)->GetStarterPoke() != nullptr && dynamic_cast<Trainer*>(player)->GetStarterPoke()->GetName() == "Bulbasaur")
	{
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect3);
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect2);
	}
	else
	{
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect1);
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect2);
		SDL_RenderCopy(Window::GetRender(), pokeballs->tex, NULL, &ballRect3);
	}
}

void OakLab::InteractWithPokeball()
{
	if (dynamic_cast<Trainer*>(player)->GetStarterPoke() == nullptr)
	{
		Dialog log;

		if (Collision::AABB(player->GetPosition(), ballInteractRect3) && Input::KeyPressed(Key::E))
		{
			name = "Charmander";
			pokemon->ChangeSprite("Assets/Pokemons/Front/Charmander.png", SDL_ScaleMode::SDL_ScaleModeBest);
			player->AddDialog("Do you wish to choose " + name + "?");
			DialogManager::GetInstance()->SetIsActive(true);
		}
		else if (Collision::AABB(player->GetPosition(), ballInteractRect2) && Input::KeyPressed(Key::E))
		{
			name = "Squirtle";
			pokemon->ChangeSprite("Assets/Pokemons/Front/Squirtle.png", SDL_ScaleMode::SDL_ScaleModeBest);
			player->AddDialog("Do you wish to choose " + name + "?");
			DialogManager::GetInstance()->SetIsActive(true);
		}
		else if (Collision::AABB(player->GetPosition(), ballInteractRect1) && Input::KeyPressed(Key::E))
		{
			name = "Bulbasaur";
			pokemon->ChangeSprite("Assets/Pokemons/Front/Bulbasaur.png", SDL_ScaleMode::SDL_ScaleModeBest);
			player->AddDialog("Do you wish to choose " + name + "?");
			DialogManager::GetInstance()->SetIsActive(true);
		}
		ChooseStarterPokemon(name);
		if (Input::KeyPressed(Key::SPACE))
		{
			player->ClearDialog();
			DialogManager::GetInstance()->SetIsActive(false);

		}
	}
	else if (Collision::AABB(dynamic_cast<Trainer*>(player)->GetPosition(), ballRect3) && Input::KeyPressed(Key::E) || Collision::AABB(dynamic_cast<Trainer*>(player)->GetPosition(), ballRect2) && Input::KeyPressed(Key::E) || Collision::AABB(dynamic_cast<Trainer*>(player)->GetPosition(), ballRect1) && Input::KeyPressed(Key::E))
	{
		//MenuHUD::OpenMessageBox();
		//message = "Better not be greedy!";
	}
}

void OakLab::ChooseStarterPokemon(std::string name)
{
	if (Input::KeyPressed(Key::Y))
	{
		player->ClearDialog();
		DialogManager::GetInstance()->SetIsActive(false);
		if (dynamic_cast<Trainer*>(player)->GetStarterPoke() == nullptr)
		{
			Pokemon* poke = CreateStarterPoke(name);
			poke->OnPokemonCreate();
			dynamic_cast<Trainer*>(player)->AddPokemonToBag(poke);
			dynamic_cast<Trainer*>(player)->SetStarterPoke(poke);
			//message = "you chose " + poke->GetName();
			std::cout << poke->GetName() << "\n";
			DialogManager::GetInstance()->ShowNextLine();
			player->AddDialog("You choose " + name + " congratulations!");
			DialogManager::GetInstance()->SetIsActive(true);
			//trainer->Quests[0]->completed = true;
		}
	}
	/*else if (Input::KeyPressed(Key::N) && MenuHUD::IsMessageBoxOpen())
		MenuHUD::CloseMessageBox();*/
}

Pokemon* OakLab::CreateStarterPoke(std::string name)
{
	if (name == "Charmander")
	{
		return new Charmander(5);
	}
	else if (name == "Squirtle")
	{
		return new Squirtle(5);
	}
	else if (name == "Bulbasaur")
	{
		return new Bulbasaur(5);
	}
	return nullptr;
}

void OakLab::InteractWithOak()
{
	
}
