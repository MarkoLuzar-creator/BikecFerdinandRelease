#pragma once
#include <string>
#include "../handlers/TextureHandler.h"
#include "../handlers/EventHandler.h"
#include "../components/Rigidbody.h"

class StaticButton
{
public:
	StaticButton(std::string text, std::string fontPath,
	std::string texture, std::string hoverTexture, float x, float y,
	int size, int r, int g, int b, int level) : text(text), fontPath(fontPath),
	texture(texture), hoverTexture(hoverTexture), x(x), y(y),
	size(size), r(r), g(g), b(b), level(level){}
	int Update(int currentLevel);
private:
	std::string text, fontPath, texture, hoverTexture;
	float x, y, size, r, g , b, level;
};

