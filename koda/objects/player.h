#pragma once
#include <string>
#include "../components/Rigidbody.h"
#include "../components/Animation.h"
#include "../handlers/TextureHandler.h"
#include "../handlers/EventHandler.h"
#include "../handlers/CameraHandler.h"

class Player
{
public:
	Player(int x, int y, int HP) : x(x), y(y), w(64), h(64), texture("player"), attackEvent(false),
	HP(HP), attack(false), healEvent(false), attackTimer(false), scale(1.5), flip(SDL_FLIP_NONE){}
	void Update(float deltaTime);
	void EnemyAttackUpdate(bool attack);
	std::pair<int, int>GetPosition(); std::pair<int, int>GetSize(); int GetHP(); bool GetAttack();
private:
	std::string texture;
	float x, y, w, h;
	bool attack, healEvent, attackEvent;
	float HP, attackTimer, scale;
	SDL_RendererFlip flip;
	Animation animation;
	RigidBody rigidbody;
};

