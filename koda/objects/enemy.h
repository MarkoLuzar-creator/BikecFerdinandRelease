#pragma once
#include "../components/Rigidbody.h"
#include "../components/Animation.h"
#include "../handlers/TextureHandler.h"
#include "../handlers/CameraHandler.h"


class Enemy
{
public:
	Enemy(int x, int y) : x(x), y(y), w(64), h(32), texture("enemy"), scale(1.5),
	attack1(false), attack2(false), randomMoveEvent(false), dirX(0), dirY(0){}
	void Update(float deltaTime, int target1PositionX, int target1PositionY, int target2PositionX, int target2PositionY, bool isAttacked);
	void UpdateCollision1(int targetPositionX, int targetPositionY, int targetSizeX, int targetSizeY);
	void UpdateCollision2(int targetPositionX, int targetPositionY, int targetSizeX, int targetSizeY);
	bool GetAttack1(); bool GetAttack2();
private:
	std::string texture;
	float x, y, w, h;
	int dirX, dirY;
	bool attack1, attack2, randomMoveEvent;
	float scale;
	RigidBody rigidbody;
	Animation animation;
};

