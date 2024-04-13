#pragma once
#include <string>
#include "../handlers/TextureHandler.h"
#include "../handlers/EventHandler.h"
#include "../components/Rigidbody.h"

class DynamicButton
{
public:
	DynamicButton(std::string text, std::string fontPath,
	std::string texture, std::string hoverTexture, float x, float y,
	int size, int r, int g, int b) : text(text), fontPath(fontPath),
	texture(texture), hoverTexture(hoverTexture), x(x), y(y),
	size(size), r(r), g(g), b(b){}
	int Update(int currentLevel, int levelToGoTo);
private:
	std::string text, fontPath, texture, hoverTexture;
	float x, y, size, r, g, b;
};

