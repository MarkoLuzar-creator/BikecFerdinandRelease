#pragma once
#include "CameraHandler.h"

CameraHandler &CameraHandler::GetInstance()
{
    static CameraHandler instance;
    return instance;
}

CameraHandler::~CameraHandler()
{
}

void CameraHandler::SetScreenSize(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void CameraHandler::Update(int targetX, int targetY, int sizeX, int sizeY)
{
    x = targetX;
    y = targetY;
    int max_x = 1920 - sizeX;
    int max_y = 1080 - sizeY;

    if (x < 0)
        x = 0;
    else if (x > max_x)
        x = max_x;

    if (y < 0)
        y = 0;
    else if (y > max_y)
        y = max_y;

    x -= screenWidth / 2 - sizeX / 2;
    y -= screenHeight / 2 - sizeY / 2;
}

void CameraHandler::GetPosition(int &x, int &y)
{
    x = this->x;
    y = this->y;
}
