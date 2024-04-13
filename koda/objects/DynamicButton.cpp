#include "DynamicButton.h"

int DynamicButton::Update(int currentLevel, int levelToGoTo)
{
	int w1, h1, w2, h2, mx1, my1;
	TextureHandler::GetInstance().GetTextSize(text, fontPath, size, w1, h1);
	TextureHandler::GetInstance().GetTextSizeScaled(text, fontPath, size, w2, h2);
	EventHandler::GetInstance().GetMousePosition(mx1, my1);

	TextureHandler::GetInstance().DrawTexture(texture, x - w2 / 2, y - h2 / 2, w1, h1, SDL_FLIP_NONE, 1);

	if (RigidBody::Collide(x - w2 / 2, y - h2 / 2, w1, h1, mx1, my1, 1, 1))
	{
		TextureHandler::GetInstance().DrawTexture(hoverTexture, x - w2 / 2, y - h2 / 2, w1, h1, SDL_FLIP_NONE, 1);
		if (EventHandler::GetInstance().GetMousePressed(SDL_BUTTON_LEFT))
		{
			return levelToGoTo;
		}
	}
	TextureHandler::GetInstance().DrawText(text, fontPath, x - w2 / 2, y - h2 / 2, size, r, g, b);
	return currentLevel;
}
