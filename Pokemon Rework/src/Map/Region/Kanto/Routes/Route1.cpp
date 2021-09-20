#include "Route1.h"

Route1::Route1(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 730);
	player->SetXYPosition(12 * tileSize * camera->GetZoom(), 12 * tileSize * camera->GetZoom());
	filePath = "Assets/Map/Routes/Route1/Route1.map";
	texturePath = "Assets/Map/Routes/Route1/Route1.png";
	imagePath = "Assets/Map/Routes/Route1/Route1Sprites.map";

	InitMap();
}

Route1::~Route1()
{
}

Map* Route1::LoadNewMap()
{
	return nullptr;
}
