#include "Bikec.h"


void Bikec::Update(float deltaTime, int targetPositionX, int targePositionY)
{
	if (!stop)
	{
		int cx, cy;
		CameraHandler::GetInstance().GetPosition(cx, cy);
		if (RigidBody::GetDistance(x, y, targetPositionX, targePositionY) < 200)
		{
			RigidBody::GetDirection(x, y, targetPositionX, targePositionY, dirX, dirY);
		}
		else
		{
			if (SDL_GetTicks64() / 100 % 10 == 0)
			{
				if (randomMoveEvent == false)
				{
					dirX = rand() % (3) - 1;
					dirY = rand() % (3) - 1;
					randomMoveEvent = true;
				}
			}
			else
			{
				randomMoveEvent = false;
			}
		}
		// Update
		rigidbody.ApplyForce(dirX * 0.5, dirY * 0.5);
		rigidbody.Update(deltaTime);
		rigidbody.Translate(x, y);

		if (dirX >= 0)
			{
				animation.SetProperties(2, 3, 500);
			}
		else if (dirX < 0)
			{
				animation.SetProperties(1, 3, 500);
			}

		// Draw
		TextureHandler::GetInstance().DrawAnimation(texture, x - cx, y - cy, w, h, animation.GetRow(),
		animation.GetFrame(), SDL_FLIP_NONE, scale);
		animation.Update();
	}
}

void Bikec::CollisionUpdate(bool attack, bool collide)
{
	if (!stop)
	{
		if ((attack == true || collide == true))
		{
			x = 9999;
			h = 9999;
			stop = true;
		}
	}
}

std::pair<int, int> Bikec::GetPosition()
{
	return std::pair<int, int>(x, y);
}

std::pair<int, int> Bikec::GetSize()
{
	return std::pair<int, int>(w * scale, h * scale);
}