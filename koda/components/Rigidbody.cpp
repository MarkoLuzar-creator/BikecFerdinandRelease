#include "Rigidbody.h"
#include <cmath>

void RigidBody::SetMass(float mass)
{
	this->mass = mass;
}

void RigidBody::SetGravity(float gravity)
{
	this->gravity = gravity;
}

void RigidBody::SetFriction(float x, float y)
{
	frictionX = x;
	frictionY = y;
}

void RigidBody::ApplyForce(float x, float y)
{
	forceX = x;
	forceY = y;
}

void RigidBody::ResetForce()
{
	forceX = 0;
	forceY = 0;
}

void RigidBody::Update(float deltaTime)
{
	accelarationX = (forceX + frictionX) / mass;
	accelarationY = gravity + forceY / mass;
	velocityX = accelarationX * deltaTime;
	velocityY = accelarationY * deltaTime;
	positionX = velocityX;
	positionY = velocityY;
}

void RigidBody::Translate(float &x, float &y)
{
	x += positionX;
	y += positionY;
}

void RigidBody::GetDirection(int x1, int y1, int x2, int y2, int &xDir, int &yDir)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	double magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (magnitude != 0)
	{
		xDir = static_cast<int>(round(deltaX / magnitude));
		yDir = static_cast<int>(round(deltaY / magnitude));
	}
	else
	{
		xDir = 0;
		yDir = 0;
	}
}

float RigidBody::GetDistance(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	return distance;
}

bool RigidBody::Collide(int x1, int y1, int sx1, int sy1, int x2, int y2, int sx2, int sy2)
{
	int minX1 = x1;
	int minY1 = y1;
	int maxX1 = x1 + sx1;
	int maxY1 = y1 + sy1;
	int minX2 = x2;
	int minY2 = y2;
	int maxX2 = x2 + sx2;
	int maxY2 = y2 + sy2;

	bool overlapX = (minX1 <= maxX2 && maxX1 >= minX2);
	bool overlapY = (minY1 <= maxY2 && maxY1 >= minY2);

	return (overlapX && overlapY);
}
