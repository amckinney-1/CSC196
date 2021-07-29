#pragma once
#include "Base/Actor.h"

class Enemy : public Engine::Actor
{
public:
	Enemy(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

	//void Draw(Core::Graphics& graphics) override;
private:
	float speed{ 200 };
	float fireTimer{ 0 };
	float fireRate{ 1 };
};