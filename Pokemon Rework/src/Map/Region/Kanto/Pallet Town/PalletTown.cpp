#include "PalletTown.h"

PalletTown::PalletTown(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, 50);

	filePath = "Assets/Map/Pallet Town/TileType/PTown.map";
	texturePath = "Assets/Map/Pallet Town/PTown.png";
	imagePath = "Assets/Map/Pallet Town/PTownSprites.map";

	InitMap();

	doors.emplace(1, std::vector<Vector2> { Vector2(0, 11), Vector2(0, 12), Vector2(0, 13)
		, Vector2(0, 14), Vector2(0, 15), Vector2(0, 16), Vector2(0, 17) });
}

PalletTown::~PalletTown()
{
}

Map* PalletTown::LoadNewMap()
{
	
}
