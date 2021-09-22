#include "Draw.h"

Draw::Draw()
{
    
}

Draw::~Draw()
{
    
}

void Draw::Update(Map* map, Character* character)
{
    this->map = map;
    this->character = character;
    DrawMapImage();
    DrawMapBackground();
    //draw after this
    DrawNpcCharacters();
    DrawCharacter();
    //draw before this
    DrawMapForeground();
}

void Draw::DrawMapImage()
{
    for (int y = 0; y < map->GetWidth(); y++)
        for (int x = 0; x < map->GetHeight(); x++)
        {
            SDL_Rect dstRect = { x * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().x, y * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().y, map->GetTileSize() * map->GetCamera()->GetZoom(), map->GetTileSize() * map->GetCamera()->GetZoom() };
            SDL_Rect srcRect = { x * map->GetTileSize(), y * map->GetTileSize(), map->GetTileSize(), map->GetTileSize() };
            SDL_RenderCopy(Window::GetRender(), map->GetTexture()->tex, &srcRect, &dstRect);
            //if (map->GetTiles()[y][x].type == TileType::Exit)
            //{
            //    SDL_SetRenderDrawColor(Window::GetRender(), 255, 0, 0, 255);
            //    SDL_Rect rect = { map->GetTiles()[y][x].textureX * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().x, map->GetTiles()[y][x].textureY * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().y, map->GetTileSize() * map->GetCamera()->GetZoom(), map->GetTileSize() * map->GetCamera()->GetZoom() };
            //    SDL_RenderDrawRect(Window::GetRender(), &rect);
            //}
            if (map->GetTiles()[y][x].type == TileType::NPC)
            {
                SDL_SetRenderDrawColor(Window::GetRender(), 0, 0, 255, 255);
                SDL_Rect rect = { map->GetTiles()[y][x].textureX * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().x, map->GetTiles()[y][x].textureY * map->GetTileSize() * map->GetCamera()->GetZoom() - map->GetCamera()->GetCamera().y, map->GetTileSize() * map->GetCamera()->GetZoom(), map->GetTileSize() * map->GetCamera()->GetZoom() };
                SDL_RenderDrawRect(Window::GetRender(), &rect);
            }
        }
}

void Draw::DrawMapBackground()
{
    for (int i = 0; i < map->GetSpriteEntities().size(); i++)
    {
        if (map->GetSpriteEntities()[i]->layer == 1)
        {
            SDL_Rect rect = { map->GetSpriteEntities()[i]->rect.x - map->GetCamera()->GetCamera().x, map->GetSpriteEntities()[i]->rect.y - map->GetCamera()->GetCamera().y, map->GetSpriteEntities()[i]->rect.w, map->GetSpriteEntities()[i]->rect.h };
            SDL_RenderCopy(Window::GetRender(), map->GetSpriteEntities()[i]->sprite->tex, NULL, &rect);
        }
    }
}

void Draw::DrawMapForeground()
{
    for (int i = 0; i < map->GetSpriteEntities().size(); i++)
    {
        if (map->GetSpriteEntities()[i]->layer == 0)
        {
            //SDL_Rect rect = { zone->GetSpriteEntities()[i]->rect.x * cam->GetZoom() - cam->GetCamera().x, zone->GetSpriteEntities()[i]->rect.y * cam->GetZoom() - cam->GetCamera().y, cam->GetZoom(), cam->GetZoom() };
            SDL_Rect rect = { map->GetSpriteEntities()[i]->rect.x - map->GetCamera()->GetCamera().x, map->GetSpriteEntities()[i]->rect.y - map->GetCamera()->GetCamera().y, map->GetSpriteEntities()[i]->rect.w, map->GetSpriteEntities()[i]->rect.h };
            SDL_RenderCopy(Window::GetRender(), map->GetSpriteEntities()[i]->sprite->tex, NULL, &rect);
        }
    }
}

void Draw::DrawCharacter()
{
    character->GetPosition().x -= map->GetCamera()->GetCamera().x;
    character->GetPosition().y -= map->GetCamera()->GetCamera().y;
    SDL_RenderCopy(Window::GetRender(), character->GetSprite()->tex, &character->GetSrcRect(), &character->GetPosition());
}

void Draw::DrawNpcCharacters()
{
    for (int i = 0; i < map->GetNpcs().size(); i++)
    {
        map->GetNpcs()[i]->GetPosition().x -= map->GetCamera()->GetCamera().x;
        map->GetNpcs()[i]->GetPosition().y -= map->GetCamera()->GetCamera().y;
        SDL_RenderCopy(Window::GetRender(), map->GetNpcs()[i]->GetSprite()->tex, &map->GetNpcs()[i]->GetSrcRect(), &map->GetNpcs()[i]->GetPosition());
    }
}
