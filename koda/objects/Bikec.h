#pragma once
#include "../components/Rigidbody.h"
#include "../components/Animation.h"
#include "../handlers/TextureHandler.h"
#include "../handlers/CameraHandler.h"

class Bikec
{
public:
	Bikec(int x, int y) : x(x), y(y), w(48), h(48), scale(0.8), randomMoveEvent(false), stop(false), dirX(0), dirY(0)
	{
		int z = rand() % (4);
		switch (z)
		{
		case 0: texture = "crni_bikec"; break;
		case 1: texture = "mesani_bikec"; break;
		case 2: texture = "rjavi_bikec"; break;
		case 3: texture = "beli_bikec"; break;
		}
	}
	void Update(float deltaTime, int targetPositionX, int targePositionY);
	void CollisionUpdate(bool attack, bool collide);
	std::pair<int, int> GetPosition(); std::pair<int, int> GetSize();
private:
	std::string texture;
	float x, y, w, h;
	int dirX, dirY;
	bool randomMoveEvent, stop;
	float scale;
	Animation animation;
	RigidBody rigidbody;
};

