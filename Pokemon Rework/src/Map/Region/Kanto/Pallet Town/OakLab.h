#pragma once
#include "../../../Map.h"
#include "../Routes/Route1.h"
#include "../../../ICheckpoint.h"

class OakLab : public Map
{
public:
	OakLab(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~OakLab();
	virtual Map* LoadNewMap() override;
	virtual void Update() override;

private:
	Map* palletTown = nullptr;

private:
	void PlacePokeballs();
	void InteractWithPokeball();
	void ChooseStarterPokemon(std::string name);
	Pokemon* CreateStarterPoke(std::string name);
	void InteractWithOak();

private:
	Sprite* pokeballs = nullptr;
	Sprite* pokemon = nullptr;
	SDL_Rect ballRect1;
	SDL_Rect ballRect2;
	SDL_Rect ballRect3;

	SDL_Rect ballInteractRect1;
	SDL_Rect ballInteractRect2;
	SDL_Rect ballInteractRect3;
	std::string name;
};