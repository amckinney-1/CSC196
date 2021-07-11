#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Graphics/Shape.h"
#include "Engine.h"
#include <iostream>
#include <vector>
#include <string>

std::vector<Engine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
Engine::Shape shape{ points, Engine::Color{1, 1, 1} };
Engine::Transform transform{ {400, 300}, 0, 3 };
const float speed = 1000;
float timer = 0;
Engine::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

Engine::Engine engine;

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

	}
	
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation +=  5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += Engine::Vector2::Rotate(Engine::Vector2::up, transform.rotation) * thrust * dt;
	transform.position.x = Engine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = Engine::Wrap(transform.position.y, 0.0f, 600.0f);
	
	engine.Get<Engine::ParticleSystem>()->Create(transform.position, 3, 2, Engine::Color::white, 50);
	engine.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics, transform.position, transform.rotation + Engine::DegToRad(180), 3);
	engine.Get<Engine::ParticleSystem>()->Draw(graphics);
	
	Engine::Color color = Engine::Lerp(Engine::Color::yellow, Engine::Color::purple, psPosition.x / 800);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());

	graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());
}

int main()
{

	char name[] = "THIS IS A WINDOW";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}