#pragma once
#include "Base/Actor.h"

class Player : public Engine::Actor
{
public:
	Player(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.1f };
	float speed{ 300 };
};