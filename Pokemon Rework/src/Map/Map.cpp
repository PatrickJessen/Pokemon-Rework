#include "Map.h"
#include "../FileHandler/simple_file_handler.h"
using namespace SimpleFileHandler;


Map::~Map()
{
    
}

void Map::InitMap()
{
    texture = new Sprite(texturePath, SDL_ScaleMode::SDL_ScaleModeNearest);
    ReadFile inFile(filePath.c_str());
    tiles = new Tile * [width];

    for (int i = 0; i < width; i++)
    {
        tiles[i] = new Tile[height];
    }

    for (int y = 0; y < width; y++)
        for (int x = 0; x < height; x++)
        {
            tiles[y][x] = inFile.ReadClass<Tile>();
        }

    LoadSpriteEntities();
}

Map* Map::LoadMap()
{
    int y = player->GetCollisionPoint().x / GetTileSize() / camera->GetZoom();
    int x = player->GetCollisionPoint().y / GetTileSize() / camera->GetZoom();
    for (auto map : GetDoorPositions())
    {
        for (int i = 0; i < map.second.size(); i++)
        {
            if (map.second[i].x == x && map.second[i].y == y)
            {
                return map.first;
            }
        }
    }
    return nullptr;
}

void Map::LoadSpriteEntities()
{
    std::ifstream fs(imagePath.c_str(), std::ifstream::in);
    //std::vector<SpriteEntity*> sprites = tileTest->sprites;
    std::string line = std::string{};
    int counter = 0;
    while (std::getline(fs, line))
    {
        std::string myPath;
        std::string rectx;
        std::string recty;
        std::string rectw;
        std::string recth;
        std::string layer;
        SDL_Rect rect = { 0, 0, 0, 0 };
        int i;
        for (i = 0; i < line.length(); i++)
        {
            if (line[i] == ';')
            {
                break;
            }
        }
        myPath.append(line, 0, i);
        int x;
        for (x = i + 1; x < line.length(); x++)
        {
            if (line[x] == ';')
            {
                break;
            }
        }
        rectx.append(line, i + 1, x - i - 1);
        int y;
        for (y = x + 1; y < line.length(); y++)
        {
            if (line[y] == ';')
            {
                break;
            }
        }
        recty.append(line, x + 1, y - x - 1);
        int w;
        for (w = y + 1; w < line.length(); w++)
        {
            if (line[w] == ';')
            {
                break;
            }
        }
        rectw.append(line, y + 1, w - y - 1);
        int h;
        for (h = w + 1; h < line.length(); h++)
        {
            if (line[h] == ';')
            {
                break;
            }
        }
        recth.append(line, w + 1, h - w - 1);
        int l;
        for (l = h + 1; l < line.length(); l++)
        {
            if (line[l] == ';')
            {
                break;
            }
        }
        layer.append(line, h + 1, l - h - 1);
        rect = { std::stoi(rectx) * camera->GetZoom(), std::stoi(recty) * camera->GetZoom(), std::stoi(rectw) * camera->GetZoom(), std::stoi(recth) * camera->GetZoom() };

        sprites.push_back(new SpriteEntity(new Sprite(myPath.c_str(), SDL_ScaleMode::SDL_ScaleModeNearest), rect, std::stoi(layer)));
    }
}
