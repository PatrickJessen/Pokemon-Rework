#include "BattleHUD.h"

void BattleHUD::SetData()
{
	TTF_Init();
	font = TTF_OpenFont("Assets/Font/arial.ttf", 30);
	fGColor = { 30, 30, 30 };
	optionText[0] = { "Fight", {30, 30, 30} };
	optionText[1] = { "Items", {30, 30, 30} };
	optionText[2] = { "Pokemon", {30, 30, 30} };
	optionText[3] = { "Run", {30, 30, 30} };
	moveText[0] = { "", {30, 30, 30} };
	moveText[1] = { "", {30, 30, 30} };
	moveText[2] = { "", {30, 30, 30} };
	moveText[3] = { "", {30, 30, 30} };
}

void BattleHUD::DrawBattleFrame()
{
	Sprite frame("Assets/BattleGrounds/Battleground frame.png", SDL_ScaleMode::SDL_ScaleModeBest);
	Sprite battleground("Assets/BattleGrounds/Grass.png", SDL_ScaleMode::SDL_ScaleModeBest);
	SDL_Rect frameRect = { 400, 200, 900, 500 };
	SDL_Rect battleRect = { frameRect.x + 7, frameRect.y + 66, frameRect.w - 228, frameRect.h - 80 };
	SDL_RenderCopy(Window::GetRender(), frame.tex, NULL, &frameRect);
	SDL_RenderCopy(Window::GetRender(), battleground.tex, NULL, &battleRect);
}

void BattleHUD::DrawTrainerEntrance(Trainer* trainer)
{
	if (trainerRect.x != 450)
	{
		trainerRect.x += 2;
	}
	SDL_RenderCopy(Window::GetRender(), trainer->GetBattleTexture()->tex, NULL, &trainerRect);
}

void BattleHUD::DrawEnemyTrainerEntrance(Trainer* enemy)
{
	if (opponentRect.x != 840)
		opponentRect.x -= 2;
	SDL_RenderCopy(Window::GetRender(), enemy->GetBattleTexture()->tex, NULL, &opponentRect);
}

void BattleHUD::DrawEnemyPokemonEntrance(Pokemon* enemy)
{
	if (opponentRect.x != 840)
		opponentRect.x -= 2;
	SDL_RenderCopy(Window::GetRender(), enemy->GetFrontTexture()->tex, NULL, &opponentRect);
}

void BattleHUD::DrawEntrance(Trainer* trainer, Pokemon* opponent)
{
}

void BattleHUD::DrawPlayerPokemonEntrance(Pokemon* player)
{
	if (pokeRect.x != 450)
	{
		pokeRect.x += 2;
	}
	SDL_RenderCopy(Window::GetRender(), player->GetBackTexture()->tex, NULL, &pokeRect);
}

void BattleHUD::DrawEnemyTrainerPokemonEntrance(Pokemon* opponent)
{
	if (opponenPoketRect.x != 840)
		opponenPoketRect.x -= 2;
	SDL_RenderCopy(Window::GetRender(), opponent->GetFrontTexture()->tex, NULL, &opponenPoketRect);
}

void BattleHUD::DrawPokemonBar(Pokemon* player, Pokemon* opponent)
{
	Sprite hpBarA("Assets/GFX/myHpBar1.png", SDL_ScaleMode::SDL_ScaleModeBest);
	Sprite hpBarP("Assets/GFX/myHpBar2.png", SDL_ScaleMode::SDL_ScaleModeBest);
	SDL_Rect hpBarARect = { 880, 610, 200, 80 };
	SDL_Rect hpBarPRect = { 407, 263, 200, 80 };
	SDL_RenderCopy(Window::GetRender(), hpBarA.tex, NULL, &hpBarARect);
	SDL_RenderCopy(Window::GetRender(), hpBarP.tex, NULL, &hpBarPRect);
	pokeName.text = player->GetName() + " LvL  " + std::to_string(player->GetLevel());
	enemyPokeName.text = opponent->GetName() + " LvL  " + std::to_string(opponent->GetLevel());
	SDL_Rect fontRect = { 900, 620, 120, 20 };
	DrawText(pokeName, fontRect);
	SDL_Rect fontRect2 = { 427, 273, 120, 20 };
	DrawText(enemyPokeName, fontRect2);
}

void BattleHUD::DrawHealthBar(SDL_Rect rect)
{
	Sprite HP("Assets/GFX/hp.png", SDL_ScaleMode::SDL_ScaleModeBest);
	SDL_RenderCopy(Window::GetRender(), HP.tex, NULL, &rect);
}

void BattleHUD::DrawOptions()
{
	std::string options[4] = { "Fight", "Items", "Pokemon", "Run" };
	//text[4] = { "Fight", fGColor, "Items", fGColor, "Pokemon", fGColor, "Run", fGColor };
	//std::string* options = new std::string[4];
	//options[0] = "Fight";
	//options[1] = "Items";
	//options[2] = "Pokemon";
	//options[3] = "Run";
	DrawHelper(4, optionText);
}

void BattleHUD::DrawMoves(Pokemon* pokemon)
{
	int x = pokemon->GetMoves().size();
	for (int i = 0; i < x; i++)
		moveText[i].text = pokemon->GetMoves()[i]->GetMoveName();

	DrawHelper(x, moveText);
}

void BattleHUD::DrawHelper(int count, Text* text)
{
	fontSize = { 1100, 200, 120, 40 };
	SDL_Color tColor = { 255, 255,255 };
	for (int i = 0; i < 4; i++)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(font, text[i].text.c_str(), text[i].color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRender(), surface);
		fontSize.y += 70;
		SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_ScaleModeBest);
		SDL_RenderCopy(Window::GetRender(), texture, NULL, &fontSize);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void BattleHUD::DrawText(Text pokeText, SDL_Rect fontRect)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, pokeText.text.c_str(), fGColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRender(), surface);
	SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_ScaleModeBest);
	SDL_RenderCopy(Window::GetRender(), texture, NULL, &fontRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void BattleHUD::UpdateActionSelection(int action)
{
	for (int i = 0; i < 4; i++)
		if (i == action)
		{
			optionText[i].color = { 0, 255, 0 };
		}
		else
		{
			optionText[i].color = { 40, 40, 40 };
		}
}

void BattleHUD::UpdateActionSelection(int action, int moveCount)
{
	for (int i = 0; i < moveCount; i++)
		if (i == action)
		{
			moveText[i].color = { 0, 255, 0 };
		}
		else
		{
			moveText[i].color = { 30, 30, 30 };
		}
}

void BattleHUD::ClearText()
{
	for (int i = 0; i < 4; i++)
		optionText[i].text = "";
}

void BattleHUD::ClearMoveText(int index)
{
	for (int i = 0; i < 4; i++)
		moveText[i].text = "";
}

Uint8 transparency = 255;
bool BattleHUD::AnimatePlayerDeath(Pokemon* pokemon)
{
	if (transparency > 0)
		transparency -= 15;
	else
		return true;

	SDL_SetTextureAlphaMod(pokemon->GetBackTexture()->tex, transparency);
	//bool isFinnished = pokeRect.y == 708;
	//if (pokeRect.y != 708)
	//{
	//	pokeRect.y += 5;
	//	pokeRect.h -= 5;
	//}
	return false;
}

bool BattleHUD::AnimateNextPlayerPokemon(Pokemon* pokemon)
{
	bool isFinnished = pokeRect.y == 608;
	if (pokeRect.y != 608)
	{
		pokeRect.y -= 5;
		pokeRect.h += 5;
	}
	return isFinnished;
}

