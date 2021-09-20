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
