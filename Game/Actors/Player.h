#pragma once
#include "Base/Actor.h"

class Player : public Engine::Actor
{
public:
	Player(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } {};

	void Update(float dt) override;
	//void Draw(Core::Graphics& graphics) override;
private:
	float speed{ 300 };
};