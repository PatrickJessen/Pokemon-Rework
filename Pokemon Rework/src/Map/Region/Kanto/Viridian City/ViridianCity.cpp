#include "ViridianCity.h"

ViridianCity::ViridianCity(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	containsCheckpoint = true;
	camera = new Camera(zoom);
	camera->SetOptions(tileSize, height, -100, 570);

	filePath = "Assets/Map/Viridian City/Viridian.map";
	texturePath = "Assets/Map/Viridian City/Viridian.png";
	imagePath = "Assets/Map/Viridian City/ViridianSprites.map";
}

ViridianCity::~ViridianCity()
{
}

Map* ViridianCity::LoadNewMap()
{
	return nullptr;
}

Map* ViridianCity::SpawnAtCheckpoint()
{
	return nullptr;
}

void ViridianCity::Update()
{
}
