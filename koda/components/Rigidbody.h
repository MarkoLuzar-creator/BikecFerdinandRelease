#pragma once

class RigidBody
{
public:
	RigidBody() : mass(1), gravity(0), positionX(0), positionY(0), frictionX(0),
	frictionY(0), velocityX(0), velocityY(0), accelarationX(0), accelarationY(0),
	forceX(0), forceY(0){}
	void SetMass(float mass);
	void SetGravity(float gravity);
	void SetFriction(float x, float y);
	void ApplyForce(float x, float y);
	void ResetForce();
	void Update(float deltaTime);
	void Translate(float &x, float &y);
	static void GetDirection(int x1, int y1, int x2, int y2, int &xDir, int &yDir);
	static float GetDistance(int x1, int y1, int x2, int y2);
	static bool Collide(int x1, int y1, int sx1, int sy1, int x2, int y2, int sx2, int sy2);
private:
	float mass, gravity;
	float positionX, positionY, frictionX, frictionY, velocityX, velocityY, accelarationX, accelarationY, forceX, forceY;
};

