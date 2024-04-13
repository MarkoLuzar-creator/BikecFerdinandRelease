#pragma once
#include "../handlers/TextureHandler.h"
#include "../components/Rigidbody.h"
#include "../handlers/CameraHandler.h"

class Arena
{
public:
	Arena(int x, int y, int count) : x(x), y(y), w(256), h(256), openDoor(false),
	stop(false), scale(1), count(count), texture("arena") { }
	int Update(int playerPositionX, int playerPositionY, int playerSizeX, int playerSizeY);
	bool OpenDoor(); int GetCount();
private:
	std::string texture;
	int x, y, w, h, count;
	bool openDoor, stop;
	float scale;
};

