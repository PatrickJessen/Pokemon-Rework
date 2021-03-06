#include "DialogManager.h"
#include <thread>
#include <chrono>

DialogManager* instance;

DialogManager::DialogManager()
{
	TTF_Init();
	font = TTF_OpenFont("Assets/Font/arial.ttf", 20);
	mBox = new Sprite("Assets/GFX/msgBox.png", SDL_ScaleMode::SDL_ScaleModeNearest);
	fontSize = { Window::GetWidth() / 2 - 190, Window::GetHeight() - 115, 400, 40 };
	instance = this;
}

DialogManager* DialogManager::GetInstance()
{
	return instance;
}

void DialogManager::ShowDialog(Dialog dialog)
{
	if (isActive)
	{
		this->dialog = dialog;
		HandleUpdate();
		DrawBox();
		TypeDialog(dialog.Lines[currentLine]);
		DrawText();
	}
}

void DialogManager::ShowNextLine()
{
	currentLine++;
	if (currentLine < dialog.Lines.size())
	{
		TypeDialog(dialog.Lines[currentLine]);
	}
	else
	{
		SetIsActive(false);
		currentLine = 0;
	}
}

void DialogManager::HandleUpdate()
{
	if (Input::KeyPressed(Key::SPACE))
	{
		ShowNextLine();
	}
}

void DialogManager::DrawBox()
{
	SDL_Rect rect = { Window::GetWidth() / 2 - 250, Window::GetHeight() - 150, 600, 150 };
	SDL_RenderCopy(Window::GetRender(), mBox->tex, NULL, &rect);
}

void DialogManager::DrawText()
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.text.c_str(), text.color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRender(), surface);
	SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_ScaleModeBest);
	SDL_RenderCopy(Window::GetRender(), texture, NULL, &fontSize);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void DialogManager::TypeDialog(std::string line)
{
	text.text = "";
	for (int i = 0; i < line.size(); i++)
	{
		text.text += line[i];
	}
}
