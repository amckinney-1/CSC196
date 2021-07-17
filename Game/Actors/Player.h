#pragma once
#include "Base/Actor.h"

class Player : public Engine::Actor
{
public:
	Player(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	//void Draw(Core::Graphics& graphics) override;
private:
	float fireTimer{ 0 };
	float fireRate{ 0.01f };
	float speed{ 300 };
};