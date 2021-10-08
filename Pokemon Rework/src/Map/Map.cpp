#include "Map.h"
#include "../FileHandler/simple_file_handler.h"
using namespace SimpleFileHandler;


Map::~Map()
{
    for (int i = 0; i < sprites.size(); i++)
    {
        delete sprites[i]->sprite;
        delete sprites[i];
    }
    sprites.clear();

    delete texture;
    doors.clear();

    for (int x = 0; x < width; x++)
    {
        delete[] tiles[x];
    }
    delete[] tiles;
    tiles = nullptr;

    for (int i = 0; i < npcs.size(); i++)
    {
        delete npcs[i];
    }
    npcs.clear();

    //delete collidedNpc;
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

    player->SetInteractPoint(player->GetXPos() + width / 2, player->GetYPos() + height / 2 + 5, 10, 10);
}

void Map::SetNpcTile()
{
    //std::cout << player->GetCollisionPoint().x / tileSize / camera->GetZoom() << " , " << player->GetCollisionPoint().y / tileSize / camera->GetZoom() << "\n";
    for (int i = 0; i < npcs.size(); i++)
    {
        if (first)
        {
            temp = TileType::Exit;
            first = false;
        }
        if (npcs[i]->GetIsWalking())
        {
            if (npcs[i]->GetDirection() == AnimationDirection::LEFT)
                tiles[npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()][(npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom()) + 1].type = temp;
            if (npcs[i]->GetDirection() == AnimationDirection::RIGHT)
                tiles[npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()][(npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom()) - 1].type = temp;
            if (npcs[i]->GetDirection() == AnimationDirection::UP)
                tiles[(npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()) + 1][(npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom())].type = temp;
            if (npcs[i]->GetDirection() == AnimationDirection::DOWN)
                tiles[(npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()) - 1][(npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom())].type = temp;

            tiles[npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()][(npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom())].type = TileType::NPC;
            first = true;
        }
        else
        {
            tiles[npcs[i]->GetCollisionPoint().y / tileSize / camera->GetZoom()][npcs[i]->GetCollisionPoint().x / tileSize / camera->GetZoom()].type = TileType::NPC;
        }
    }
}

int Map::EnterDoor(int camX, int camY)
{
    int x = player->GetInteractPoint().x / tileSize / camera->GetZoom();
    int y = player->GetInteractPoint().y / tileSize / camera->GetZoom();
    //std::cout << x << ", " << y << "\n";
    for (int i = 0; i < doors.size(); i++)
    {
        for (int j = 0; j < doors[i].size(); j++)
        {
            //std::cout << doorsPosition[i][j].x << ", " << doorsPosition[i][j].y << " : " << x << ", " << y << "\n";
            if (y == doors[i][j].x && x == doors[i][j].y)
            {
                return i;
            }
        }
    }
    return -1;
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

Character* Map::GetCharacterByName(std::string name)
{
    for (int i = 0; i < npcs.size(); i++)
    {
        if (name == npcs[i]->GetName())
            return npcs[i];
    }
    return nullptr;
}
