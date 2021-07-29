#include "Player.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"

Player::Player(const Engine::Transform& transform, std::shared_ptr<Engine::Shape> shape, float speed) : Engine::Actor{ transform, shape }, speed{ speed } 
{
	
}

void Player::Initialize()
{
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = Engine::Vector2{ 0, 5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = Engine::Vector2{ 0, -5 };
	AddChild(std::move(locator));

	std::unique_ptr engine = std::make_unique<Actor>(Engine::Transform{}, scene->engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("shape.txt"));
	engine->transform.localPosition = Engine::Vector2{ 8, 0 };
	engine->transform.localRotation = Engine::DegToRad(180);
	AddChild(std::move(engine));
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//children[2]->transform.localRotation += 5 * dt;

	// movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	// acceleration
	Engine::Vector2 acceleration;
	acceleration += Engine::Vector2::Rotate(Engine::Vector2::right, transform.rotation) * thrust;
	//Engine::Vector2 gravity = (Engine::Vector2{ 400, 300 } - transform.position).Normalized() * 200; // Swap direction and normalized for repulsion 
	//Engine::Vector2 gravity = Engine::Vector2::down * 200;
	//acceleration += gravity;
	
	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.985f; //Inertial Dampening

	transform.position.x = Engine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = Engine::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;

		Engine::Transform t = children[0]->transform;
		t.scale = 0.5f;

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("shape.txt"), 600);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
		scene->engine->Get<Engine::AudioSystem>()->PlayAudio("PlayerShoot");
	}

	std::vector<Engine::Color> colors = { Engine::Color::purple, Engine::Color::cyan, Engine::Color::blue };
	scene->engine->Get<Engine::ParticleSystem>()->Create(children[2]->transform.position, 3, 2, colors, 75, children[0]->transform.rotation, Engine::DegToRad(30));
}

void Player::OnCollision(Actor* actor)
{
	return;

	if (dynamic_cast<Enemy*>(actor))
	{
		destroy = true;
		scene->engine->Get<Engine::ParticleSystem>()->Create(transform.position, 200, 1, Engine::Color::white, 100);
		scene->engine->Get<Engine::AudioSystem>()->PlayAudio("PlayerExplosion");

		Engine::Event event;
		/*event.name = "PlayerDead";
		event.data = std::string("yes i'm dead!");
		scene->engine->Get<Engine::EventSystem>()->Notify(event);*/
	}
}
