#include "Door.h"

std::pair<int, bool> Door::Update(bool isOpen, int playerPositionX, int playerPositionY, int playerSizeX, int playerSizeY, int currentLevel)
{
	int cx, cy;
	CameraHandler::GetInstance().GetPosition(cx, cy);
	std::pair<int, bool> rValues;
	rValues.first = currentLevel;
	rValues.second = false;
	// Animations + Logic
	if (isOpen == true) {
		if (RigidBody::Collide(x, y, w, h, playerPositionX, playerPositionY, playerSizeX, playerSizeY))
		{
			rValues.first = level;
			rValues.second = true;
			return rValues;
		}
		animation.SetProperties(2, 3, 50);
	}
	else {
		animation.SetProperties(0, 9, 500);
	}
	// Draw + Update
	TextureHandler::GetInstance().DrawAnimation(texture, x - cx, y - cy,
	w, h, animation.GetRow(), animation.GetFrame(), SDL_FLIP_NONE, 1.0f);
	animation.Update();
	return rValues;
}
