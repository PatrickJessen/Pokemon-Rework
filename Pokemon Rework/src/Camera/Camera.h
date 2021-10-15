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
	/// <summary>
	/// Used to set which target the camera should focus on
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(SDL_Rect* target);
	SDL_Rect* GetTarget() { return target; }
	int GetZoom() { return zoom; }
	void SetZoom(int value) { zoom = value; }
	void SetOptions(int tileSize, int height, int extra);
	void SetOptions(int tileSize, int height, int extra, int extraWidth);

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
	int extraWidth = 0;
};