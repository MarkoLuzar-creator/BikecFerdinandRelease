#include "Player.h"

void Player::Update(float deltaTime)
{
	// Reset
	attack = false;
	int dirX = 0, dirY = 0;
	int cx, cy;
	CameraHandler::GetInstance().GetPosition(cx, cy);

	// Movement
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_A))
	{
		dirX -= 1;
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_D))
	{
		dirX += 1;
		flip = SDL_FLIP_NONE;
	}
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_S))
	{
		dirY += 1;
	}
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_W))
	{
		dirY -= 1;
	}

	// Animation
	if (attackEvent == false)
	{
		if (dirX == 0)
		{
			animation.SetProperties(0, 5, 100);
		}
		if (dirX != 0)
		{
			animation.SetProperties(1, 8, 100);
		}
	}
	else
	{
		animation.SetProperties(4, 6, 100);
		if (animation.GetFrame() == 4)
		{
			attackEvent = false;
		}
	}

	// Draw
	TextureHandler::GetInstance().DrawAnimation(texture, x - cx,
	y - cy, w, h, animation.GetRow(), animation.GetFrame(), flip, scale);
	
	// Update
	CameraHandler::GetInstance().Update(x, y, w, h);
	animation.Update();

	// Move
	rigidbody.ApplyForce(dirX * 5, dirY * 5);
	rigidbody.Update(deltaTime);
	rigidbody.Translate(x, y);

	// HP bar
	TextureHandler::GetInstance().DrawTexture("blue", x - cx + 5,
	y - cy, 50 / ((float)100 / HP), 10, SDL_FLIP_NONE, scale);

	// Combat
	if (EventHandler::GetInstance().GetKeyPressed(SDL_SCANCODE_RETURN))
	{
		attack = true;
		attackEvent = true;
	}
}

void Player::EnemyAttackUpdate(bool attack)
{
	// Healing and taking damage
	if (attack == true)
	{
		HP -= 10;
		attackTimer = SDL_GetTicks64() / 1000;
	}
	if (SDL_GetTicks64() / 1000 - attackTimer == 10)
	{
		if (healEvent == false)
		{
			if (HP != 100)
			{
				HP += 10;
				attackTimer += 10;
			}
			healEvent = true;
		}
	}
	else
	{
		healEvent = false;
	}
}

int Player::GetHP()
{
	return HP;
}

std::pair<int, int> Player::GetPosition()
{
	return std::pair<int, int>(x, y);
}

std::pair<int, int> Player::GetSize()
{
	return std::pair<int, int>(w * scale, h * scale);
}

bool Player::GetAttack()
{
	return attack;
}

