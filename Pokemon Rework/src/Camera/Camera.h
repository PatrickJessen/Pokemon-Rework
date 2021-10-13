#pragma once
#include "../Window/Window.h"

class Camera
{
public:
	Camera(int zoom);
	~Camera();

public:
	void Update();
	SDL_Rect GetCamera() { return cam; }
	SDL_Rect SetCamera() { return cam; }
	void SetTarget(SDL_Rect* target);
	SDL_Rect* GetTarget() { return target; }
	int GetZoom() { return zoom; }
	void SetZoom(int value) { zoom = value; }
	void SetOptions(int tileSize, int height, int extra);

public:
	void SetFollowPlayer(bool value) { followPlayer = value; }

private:
	SDL_Rect point;
	SDL_Rect cam;
	SDL_Rect* target;
	int zoom;
	bool followPlayer = true;
	int tileSize;
	int height;
	int extra;
};