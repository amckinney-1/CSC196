#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

#include <iostream>
#include <vector>
#include <string>

std::vector<Engine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };

Engine::Transform transform{ {400, 300}, 0, 3 };
const float speed = 1000;
float timer = 0;
Engine::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

Engine::Engine engine;
Engine::Scene scene;


bool Update(float dt)
{
	deltaTime = dt;
	gameTime += deltaTime;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	int x, y;
	Core::Input::GetMousePos(x, y);
	
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);

	timer += dt * 5;
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		std::vector<Engine::Color> colors{ Engine::Color::white, Engine::Color::orange };
		engine.Get<Engine::ParticleSystem>()->Create(psPosition, 150, 2, colors[Engine::RandomRangeInt(0, colors.size())], 150);
		engine.Get<Engine::AudioSystem>()->PlayAudio("explosion");
	}
	//engine.Get<Engine::ParticleSystem>()->Create(transform.position, 3, 2, Engine::Color::white, 50);
	
	scene.GetActor<Player>()->shape->color = Engine::Color{ Engine::Random(), Engine::Random(), Engine::Random() };
	scene.GetActor<Enemy>()->shape->color = Engine::Color{ Engine::Random(), Engine::Random(), Engine::Random() };

	engine.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	float scale = 1 + (std::sin(timer) + 1) * 2;
	engine.Get<Engine::ParticleSystem>()->Draw(graphics);
	
	Engine::Color color = Engine::Lerp(Engine::Color::yellow, Engine::Color::purple, psPosition.x / 800);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());
	graphics.DrawString(10, 50, std::to_string(scene.GetActors<Projectile>().size()).c_str());
	scene.Draw(graphics);
}

void Init()
{
	std::shared_ptr<Engine::Shape> shape = std::make_shared<Engine::Shape>();
	shape->Load("shape.txt");

	std::shared_ptr<Engine::Shape> shape1 = std::make_shared<Engine::Shape>( points, Engine::Color{1, 1, 1} );
	std::shared_ptr<Engine::Shape> shape2 = std::make_shared<Engine::Shape>( points, Engine::Color{0, 1, 1} );

	engine.Get<Engine::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(std::make_unique<Player>( Engine::Transform{ Engine::Vector2{400, 300}, 0, 3 }, shape, 300 ));
	
	for (size_t i = 0; i < 100; i++)
	{
		scene.AddActor(std::make_unique<Enemy>( Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 2 }, shape2, 300 ));
	}
	
}

int main()
{

	char name[] = "THIS IS A WINDOW";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();
	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}