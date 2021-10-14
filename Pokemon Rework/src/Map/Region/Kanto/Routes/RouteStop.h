#pragma once
#include "../../../Map.h"

class RouteStop : public Map
{
public:
	RouteStop(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom, bool isVertical);
	~RouteStop();

	virtual Map* LoadNewMap() override;
	virtual void Update() override;
};