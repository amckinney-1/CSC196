#pragma once
#include "Base/Actor.h"

class Projectile : public Engine::Actor
{
public:
	Projectile(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	//void Draw(Core::Graphics& graphics) override;
private:
	float lifetime{ 2 };
	float speed{ 300 };
};