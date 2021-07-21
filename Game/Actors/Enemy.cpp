#include "Enemy.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	transform.position += Engine::Vector2::Rotate(Engine::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = Engine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = Engine::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor))
	{
		actor->destroy = true;

		destroy = true;
		scene->engine->Get<Engine::ParticleSystem>()->Create(transform.position, 200, 1, Engine::Color::white, 100);
		scene->engine->Get<Engine::AudioSystem>()->PlayAudio("explosion");

		Engine::Event event;
		event.name = "AddPoints";
		scene->engine->Get<Engine::EventSystem>()->Notify(event);
	}
}