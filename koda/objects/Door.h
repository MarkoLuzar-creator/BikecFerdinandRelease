#pragma once
#include "../components/Animation.h"
#include "../components/Rigidbody.h"
#include "../handlers/CameraHandler.h"
#include "../handlers/TextureHandler.h"

class Door
{
public:
	Door(int x, int y, int level) : x(x), y(y), texture("door"),
	w(240), h(240), level(level){}
	std::pair<int, bool> Update(bool isOpen, int playerPositionX, int playerPositionY, int playerSizeX, int playerSizeY, int currentLevel);
private:
	std::string texture;
	int x, y, w, h, level;
	Animation animation;
};

