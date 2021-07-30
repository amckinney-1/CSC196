#pragma once
#include "Base/Actor.h"

class Asteroid : public Engine::Actor
{
public:
	Asteroid(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
private:
	float speed{ 200 };
};