#include "RouteStop.h"
#include "Route1.h"
#include "../Viridian City/ViridianCity.h"

RouteStop::RouteStop(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom, bool isVertical)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->zoneLevel = zoneLevel;
	this->player = player;
	containsCheckpoint = false;
	camera = new Camera(zoom);

	if (isVertical)
	{
		filePath = "Assets/Map/RouteStop/RouteStop.map";
		texturePath = "Assets/Map/RouteStop/RouteStop.png";
	}

	camera->SetZoom(1);
	camera->SetFollowPlayer(false);
	camera->SetOptions(tileSize, height, 0);

	doors.emplace(0, std::vector<Vector2> {Vector2(2, 6), Vector2(2, 7), Vector2(2, 7)});
	doors.emplace(1, std::vector<Vector2> {Vector2(23, 5), Vector2(23, 6), Vector2(23, 7), Vector2(23, 8), Vector2(23, 9)});
}

RouteStop::~RouteStop()
{
}

Map* RouteStop::LoadNewMap()
{
	int x = EnterDoor(camera->GetCamera().x, camera->GetCamera().y);
	switch (x)
	{
	case 0:
	{
		ViridianCity* viridian = new ViridianCity(player, 40, 40, 32, 1, 2);
		player->SetXYPosition(10 * tileSize * viridian->GetCamera()->GetZoom() - 5, 10 * tileSize * viridian->GetCamera()->GetZoom() - 8);
		return viridian;
	}
	break;
	case 1:
	{
		Route1* route1 = new Route1(player, 51, 51, 32, 2, 2);
		player->SetXYPosition(13 * tileSize * route1->GetCamera()->GetZoom() - 5, 6 * tileSize * route1->GetCamera()->GetZoom() - 8);
		return route1;
	}
	break;
	}
	return nullptr;
}

void RouteStop::Update()
{
}
