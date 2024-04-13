#include "Enemy.h"

void Enemy::Update(float deltaTime, int target1PositionX, int target1PositionY, int target2PositionX, int target2PositionY, bool isAttacked)
{
	int cx, cy;
	CameraHandler::GetInstance().GetPosition(cx, cy);

	// Napredni AI
	if (RigidBody::GetDistance(x, y, target1PositionX, target1PositionY) < 300)
	{
		RigidBody::GetDirection(x, y, target1PositionX, target1PositionY, dirX, dirY);
	}
	else if (RigidBody::GetDistance(x, y, target1PositionX, target1PositionY) < 300)
	{
		RigidBody::GetDirection(x, y, target2PositionX, target2PositionY, dirX, dirY);
	}
	else if (RigidBody::GetDistance(x, y, target1PositionX, target1PositionY) > 1000)
	{
		RigidBody::GetDirection(x, y, target1PositionX, target1PositionY, dirX, dirY);
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

	// Move
	rigidbody.ApplyForce(dirX * 0000.1, dirY * 0000.1);
	rigidbody.Update(deltaTime);
	rigidbody.Translate(x, y);

	// Draw
	animation.SetProperties(0, 5, 50);
	TextureHandler::GetInstance().DrawAnimation(texture, x - cx,
	y - cy, w, h, animation.GetRow(),
	animation.GetFrame(), SDL_FLIP_NONE, scale);
	animation.Update();

	// Combat
	if (isAttacked == true && RigidBody::GetDistance(x, y, target1PositionX, target1PositionY) < 300)
	{
		x = rand() % 1920;
		y = rand() % 1080;
	}
}

void Enemy::UpdateCollision1(int targetPositionX, int targetPositionY, int targetSizeX, int targetSizeY)
{
	if (RigidBody::Collide(x, y, w, h, targetPositionX, targetPositionY, targetSizeX, targetSizeY))
	{
		x = rand() % 1920;
		y = rand() % 1080;
		attack1 = true;
	}
}

void Enemy::UpdateCollision2(int targetPositionX, int targetPositionY, int targetSizeX, int targetSizeY){
	if (RigidBody::Collide(x, y, w, h, targetPositionX, targetPositionY, targetSizeX, targetSizeY))
	{
		attack2 = true;
	}
}

bool Enemy::GetAttack1()
{
	bool tempAttack = attack1;
	attack1 = false;
	return tempAttack;
}

bool Enemy::GetAttack2()
{
	bool tempAttack = attack2;
	attack2 = false;
	return tempAttack;
}
