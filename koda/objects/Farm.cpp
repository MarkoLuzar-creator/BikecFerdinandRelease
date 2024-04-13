#include "Farm.h"

void Farm::Update()
{
	int cx, cy;
	CameraHandler::GetInstance().GetPosition(cx, cy);
	// Draw
	TextureHandler::GetInstance().DrawTexture(texture, x - cx,
	y - cy, w, h, SDL_FLIP_NONE, scale);
}

bool Farm::CheckCollisions(int obsPositionX, int obsPositionY, int obsSizeX, int obsSizeY)
{
	// Collision + Points
	if (RigidBody::Collide(x, y, w, h, obsPositionX, obsPositionY, obsSizeX, obsSizeY))
	{
		points = 100;
		return true;
	}
	return false;
}

int Farm::GetPoints()
{
	int tempPoints = points;
	points = 0;
	return tempPoints;
}
