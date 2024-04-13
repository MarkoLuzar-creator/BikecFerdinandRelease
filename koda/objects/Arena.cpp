#include "Arena.h"

int Arena::Update(int playerPositionX, int playerPositionY, int playerSizeX, int playerSizeY)
{
	if (!openDoor)
	{
		int cx, cy;
		CameraHandler::GetInstance().GetPosition(cx, cy);
		if (RigidBody::Collide(x, y, w, h, playerPositionX, playerPositionY, playerSizeX, playerSizeY))
		{
			x = rand() % (1920);
			y = rand() % (1080);
			if (count == 1)
			{
				openDoor = true;
				stop = true;
				return 50;
			}
			count--;
			return 25;
		}

		if (RigidBody::GetDistance(x, y, playerPositionX, playerPositionY) < 500)
		{
			TextureHandler::GetInstance().DrawTexture(texture, x - cx,
				y - cy, w, h, SDL_FLIP_NONE, scale);
		}
	}

	return 0;
}

bool Arena::OpenDoor()
{
	return openDoor;
}

int Arena::GetCount()
{
	return count;
}
