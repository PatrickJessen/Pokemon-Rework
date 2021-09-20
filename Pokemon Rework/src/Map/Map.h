#pragma once
#include <string>
#include <map>
#include <vector>
#include "SDL.h"
#include "../Core/SpriteEntity.h"
#include "../Camera/Camera.h"
#include "../Core/Vector2.h"
#include "../Character/Character.h"

//tile types to know what we walk on
enum class TileType
{
	Depth, Water, Collision, Door, Exit, Grass, TallGrass, Grave, Sand, Rock, DeepWater, Ice, Waterfall, Bumpers, NPC
};

struct Tile
{
	int textureX;
	int textureY;
	TileType type;
};

//abstract class
class Map
{
public:
	virtual ~Map();
	virtual Map* LoadNewMap() = 0;

public:
	//Gets width of the zone
	int GetWidth() const { return width; }
	//Gets height of the zone
	int GetHeight() const { return height; }
	//Gets tileSize of the zone
	int GetTileSize() const { return tileSize; }
	//Gets all the sprites used in the map
	std::vector<SpriteEntity*> GetSpriteEntities() { return sprites; }
	//Gets background texture;
	Sprite* GetTexture() { return texture; }
	Tile** GetTiles() { return tiles; }
	Camera* GetCamera() { return camera; }
	std::map<Map*, std::vector<Vector2>> GetDoorPositions() { return doors; }

	Map* LoadMap();

private:
	void LoadSpriteEntities();

protected:
	//Initializes map / creating dynamic 2d array of tile struct
	void InitMap();
	Tile** tiles;
	std::string filePath;
	std::string texturePath;
	std::string imagePath;
	int width;
	int height;
	int tileSize;
	int zoneLevel;
	Camera* camera = nullptr;
	std::map<Map*, std::vector<Vector2>> doors;
	Character* player;

private:

private:
	std::vector<SpriteEntity*> sprites;
	Sprite* texture = nullptr;
};