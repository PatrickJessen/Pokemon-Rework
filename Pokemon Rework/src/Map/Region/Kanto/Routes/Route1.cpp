#include "Route1.h"

Route1::Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 730);
	
	filePath = "Assets/Map/Routes/Route1/Route1.map";
	texturePath = "Assets/Map/Routes/Route1/Route1.png";
	imagePath = "Assets/Map/Routes/Route1/Route1Sprites.map";

	doors.emplace(0, std::vector<Vector2> {Vector2(50, 12), Vector2(50, 13), Vector2(50, 14), Vector2(50, 15), Vector2(50, 16), Vector2(50, 17), Vector2(50, 18)});
}

Route1::~Route1()
{
	
}

Map* Route1::LoadNewMap()
{
	int x = EnterDoor(camera->GetCamera().x, camera->GetCamera().y);
	switch (x)
	{
	case 0:
	{
		pTown = new PalletTown(player, 31, 31, 32, 1, 2);
		player->SetXYPosition(14 * tileSize * camera->GetZoom(), 1 * tileSize * camera->GetZoom());
		return pTown;
	}
	break;
	case 1:
	{
		
	}
	break;
	}
	return nullptr;
}
