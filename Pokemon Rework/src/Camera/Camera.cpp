#include "Camera.h"

Camera::Camera(int zoom)
{
    this->zoom = zoom;
}

Camera::~Camera()
{
}

void Camera::Update()
{
    if (followPlayer)
    {
        int temp = (tileSize * height) + extra;
        cam.x = (((target->x) + target->w / 2) - Window::GetWidth() / 2);
        cam.y = (((target->y) + target->h / 2) - Window::GetHeight() / 2);
        if (cam.x < 0)
            cam.x = 0;
        if (cam.y < 0)
            cam.y = 0;
        if (cam.x > (Window::GetWidth() / 6 - cam.w) + extraWidth)
            cam.x = (Window::GetWidth() / 6 - cam.w) + extraWidth;
        if (cam.y > temp)
            cam.y = temp;
    }
    else
    {
        cam.x = (Window::GetWidth() / 2) - 1300;
        cam.y = -90;
    }

    //std::cout << trainer->GetTileX(tileSize) + cam.x / tileSize << ", " << trainer->GetTileY(tileSize) + cam.y / tileSize << "\n";
}

//void Camera::SetLevel(Level* level)
//{
//    this->level = level;
//}

void Camera::SetTarget(SDL_Rect* target)
{
    this->target = target;
}

void Camera::SetOptions(int tileSize, int height, int extra)
{
    this->tileSize = tileSize;
    this->height = height;
    this->extra = extra;
}

void Camera::SetOptions(int tileSize, int height, int extra, int extraWidth)
{
    this->tileSize = tileSize;
    this->height = height;
    this->extra = extra;
    this->extraWidth = extraWidth;
}
