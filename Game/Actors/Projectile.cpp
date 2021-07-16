#include "Projectile.h"
#include "Math/MathUtils.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += Engine::Vector2::Rotate(Engine::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = Engine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = Engine::Wrap(transform.position.y, 0.0f, 600.0f);

}