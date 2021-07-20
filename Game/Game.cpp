#include "Game.h"

#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<Engine::Engine>(); // new Engine
	engine->Startup();
	scene = std::make_unique<Engine::Scene>();
	scene->engine = engine.get();

	engine->Get<Engine::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	//(this->*stateFunction(dt));

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		std::vector<Engine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };

		std::shared_ptr<Engine::Shape> shape = std::make_shared<Engine::Shape>();
		shape->Load("shape.txt");

		//std::shared_ptr<Engine::Shape> shape1 = std::make_shared<Engine::Shape>( points, Engine::Color{1, 1, 1} );
		std::shared_ptr<Engine::Shape> shape2 = std::make_shared<Engine::Shape>(points, Engine::Color{ 0, 1, 1 });


		scene->AddActor(std::make_unique<Player>(Engine::Transform{ Engine::Vector2{400, 300}, 0, 3 }, shape, 300.0f));

		for (size_t i = 0; i < 100; i++)
		{
			scene->AddActor(std::make_unique<Enemy>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 2 }, shape2, 300.0f));
		}

		state = eState::Game;

	}
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		
		//graphics.SetBackgroundColor(Engine::Color::cyan);
		graphics.SetColor(Engine::Color::purple);

		graphics.DrawString(320, 300 + static_cast<int>(std::sin(stateTimer * 10) * 20), "[Insert Game Title Here]");
		graphics.DrawString(320, 400, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}
	graphics.SetColor(Engine::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(770, 20, std::to_string(lives).c_str());
	scene->Draw(graphics);
	engine->Get<Engine::ParticleSystem>()->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		//stateFunction = &Game::UpdateTitle;
		//state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt)
{
	std::vector<Engine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };

	std::shared_ptr<Engine::Shape> shape = std::make_shared<Engine::Shape>();
	shape->Load("shape.txt");

	//std::shared_ptr<Engine::Shape> shape1 = std::make_shared<Engine::Shape>( points, Engine::Color{1, 1, 1} );
	std::shared_ptr<Engine::Shape> shape2 = std::make_shared<Engine::Shape>(points, Engine::Color{ 0, 1, 1 });


	scene->AddActor(std::make_unique<Player>(Engine::Transform{ Engine::Vector2{400, 300}, 0, 3 }, shape, 300.0f));

	for (size_t i = 0; i < 100; i++)
	{
			scene->AddActor(std::make_unique<Enemy>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 2 }, shape2, 300.0f));
	}
}
