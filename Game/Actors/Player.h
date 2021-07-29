#pragma once
#include "Base/Actor.h"

class Player : public Engine::Actor
{
public:
	Player(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.1f };
	float speed{ 100 };
	Engine::Vector2 velocity;
};