#include "Route1.h"
#include "RouteStop.h"

Route1::Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	containsCheckpoint = false;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 730);
	
	filePath = "Assets/Map/Routes/Route1/Route1.map";
	texturePath = "Assets/Map/Routes/Route1/Route1.png";
	imagePath = "Assets/Map/Routes/Route1/Route1Sprites.map";

	doors.emplace(0, std::vector<Vector2> {Vector2(50, 12), Vector2(50, 13), Vector2(50, 14), Vector2(50, 15), Vector2(50, 16), Vector2(50, 17), Vector2(50, 18)});
	doors.emplace(1, std::vector<Vector2> {Vector2(4, 13), Vector2(4, 14)});

	//pokesInThisZone.push_back(SpawnPokes(new Pidgey((rand() + zoneLevel + 1) % 6), 100, 70));
	//pokesInThisZone.push_back(SpawnPokes(new Rattata((rand() + zoneLevel + 1) % 6), 100, 70));
	pokesInThisZone.push_back(SpawnPokes(new Rattata(3), 100, 70));
}

Route1::~Route1()
{
	for (int i = 0; i < pokesInThisZone.size(); i++)
	{
		delete pokesInThisZone[i].Pokemon;
	}
	pokesInThisZone.clear();
}

Map* Route1::LoadNewMap()
{
	int x = EnterDoor(camera->GetCamera().x, camera->GetCamera().y);
	switch (x)
	{
	case 0:
	{
		pTown = new PalletTown(player, 31, 31, 32, 1, 2);
		player->SetXYPosition(14 * tileSize * camera->GetZoom() - 5, 1 * tileSize * camera->GetZoom() - 8);
		return pTown;
	}
	break;
	case 1:
	{
		RouteStop* routeStop = new RouteStop(player, 25, 25, 32, 2, 1, true);
		player->SetXYPosition(7 * tileSize * routeStop->GetCamera()->GetZoom() - 5, 22 * tileSize * routeStop->GetCamera()->GetZoom() - 8);
		return routeStop;
	}
	break;
	}
	return nullptr;
}

Pokemon* Route1::SpawnPokemon()
{
	spawnedPoke = pokesInThisZone[Random::InRange(0, pokesInThisZone.size())].Pokemon;
	spawnedPoke->SetLevel(5);
	spawnedPoke->OnPokemonCreate();
	return spawnedPoke;
}

Map* Route1::SpawnAtCheckpoint()
{
	return lastCheckpoint;
}

void Route1::Update()
{
}
