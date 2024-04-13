#include "StaticButton.h"

int  StaticButton::Update(int currentLevel)
{
	int w1, h1, w2, h2, mx, my;
	EventHandler::GetInstance().GetMousePosition(mx, my);
	TextureHandler::GetInstance().GetTextSize(text, fontPath,size, w1, h1);
	TextureHandler::GetInstance().GetTextSizeScaled(text, fontPath, size, w2, h2);

	// DRAW
	TextureHandler::GetInstance().DrawTexture(texture, x - w2 / 2, y - h2 / 2, w1, h1, SDL_FLIP_NONE, 1);

	if (RigidBody::Collide(x - w2 / 2, y - h2 / 2, w1, h1, mx, my, 1, 1))
	{

		TextureHandler::GetInstance().DrawTexture(hoverTexture, x - w2 / 2, y - h2 / 2, w1, h1, SDL_FLIP_NONE, 1);
		if (EventHandler::GetInstance().GetMousePressed(SDL_BUTTON_LEFT))
		{
			return level;
		}
	}
	TextureHandler::GetInstance().DrawText(text, fontPath, x - w2 / 2, y - h2 / 2, size, r, g, b);
	return currentLevel;
}