#pragma once
#include <string>
#include "../handlers/CameraHandler.h"
#include "../handlers/TextureHandler.h"
#include "../components/Rigidbody.h"

class Farm
{
public:
	Farm(int x, int y) : x(x), y(y), w(336), h(336), texture("Barn"), points(0), scale(1){}
	void Update();
	bool CheckCollisions(int obsPositionX, int obsPositionY, int obsSizeX, int obsSizeY);
	int GetPoints();
private:
	std::string texture;
	int x, y, w, h, points;
	float scale;
};

