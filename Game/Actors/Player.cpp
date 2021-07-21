#include "Player.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	// movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += Engine::Vector2::Rotate(Engine::Vector2::right, transform.rotation) * thrust * dt;
	transform.position.x = Engine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = Engine::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;
		std::vector<Engine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
		std::shared_ptr<Engine::Shape> shape = std::make_shared<Engine::Shape>(points, Engine::Color{ 0, 1, 1 });

		Engine::Transform t = transform;
		t.scale = 0.5f;
		scene->AddActor(std::make_unique<Projectile>(t, shape, 600));
	}

	scene->engine->Get<Engine::ParticleSystem>()->Create(transform.position, 3, 2, Engine::Color::white, 75);

}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor))
	{
		destroy = true;
		scene->engine->Get<Engine::ParticleSystem>()->Create(transform.position, 200, 1, Engine::Color::white, 100);
		scene->engine->Get<Engine::AudioSystem>()->PlayAudio("explosion");

		Engine::Event event;
		event.name = "PlayerDead";
		scene->engine->Get<Engine::EventSystem>()->Notify(event);
	}
}
