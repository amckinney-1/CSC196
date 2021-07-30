#include "Game.h"

#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Asteroid.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<Engine::Engine>(); // new Engine
	engine->Startup();
	scene = std::make_unique<Engine::Scene>();
	scene->engine = engine.get();

	engine->Get<Engine::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<Engine::AudioSystem>()->AddAudio("PlayerShoot", "PlayerShoot.wav");
	engine->Get<Engine::AudioSystem>()->AddAudio("EnemyShoot", "EnemyShoot.wav");
	engine->Get<Engine::AudioSystem>()->AddAudio("PlayerExplosion", "PlayerExplosion.wav");
	engine->Get<Engine::AudioSystem>()->AddAudio("EnemyExplosion", "EnemyExplosion.wav");
	engine->Get<Engine::AudioSystem>()->AddAudio("music", "music.mp3");
	
	engine->Get<Engine::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<Engine::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			scene->engine->Get<Engine::AudioSystem>()->PlayAudio("music");
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		levelTimer = 0;
		level++;
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	case Game::eState::Game:
		levelTimer += dt;
		if (levelTimer >= 15)
		{
			levelTimer -= 5;
			int spawnNumber = Engine::RandomRangeInt(1 + level, 3 + level);

			for (int i = 0; i <= spawnNumber; i++)
			{
				scene->AddActor(std::make_unique<Asteroid>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800.0f), 0.0f}, Engine::RandomRange(0, Engine::TwoPi), Engine::RandomRange(1, 7) }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("Asteroid.txt"), 300.0f));
			}
		}
		if (lives > 0 && !scene->GetActor<Player>())
		{
			lives--;
			scene->AddActor(std::make_unique<Player>(Engine::Transform{ Engine::Vector2{400, 300}, 0, 5 }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("PlayerShape.txt"), 300.0f));
		}
		if (lives <= 0 && !scene->GetActor<Player>())
		{
			state = eState::GameOver;
		}
		else if (scene->GetActors<Enemy>().size() == 0)
		{
			state = eState::StartLevel;
		}
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
		graphics.SetColor(Engine::Color::red);
		graphics.DrawString(320, 400, "GAME OVER");
		break;
	default:
		break;
	}
	graphics.SetColor(Engine::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(400, 20, std::to_string(level).c_str());
	graphics.DrawString(770, 20, std::to_string(lives).c_str());
	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateLevelStart(float dt)
{
	if (!scene->GetActor<Player>())
	{
		scene->AddActor(std::make_unique<Player>(Engine::Transform{ Engine::Vector2{400, 300}, 0, 5 }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("PlayerShape.txt"), 300.0f));
	}

	for (size_t i = 0; i < level * 2; i++)
	{
		float f = Engine::RandomRange(0, 10);
		if (f <= 7.6)
		{
			scene->AddActor(std::make_unique<Enemy>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 2 }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("EnemyShape.txt"), 150.0f));
		}
		else if (f <= 9)
		{
			scene->AddActor(std::make_unique<Enemy>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 5 }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("EnemyShooter.txt"), 100.0f, true));
		}
		else
		{
			scene->AddActor(std::make_unique<Enemy>(Engine::Transform{ Engine::Vector2{Engine::RandomRange(0.0f, 800),Engine::RandomRange(0.0f, 600)}, Engine::RandomRange(0, Engine::TwoPi), 5 }, engine->Get<Engine::ResourceSystem>()->Get<Engine::Shape>("EnemyBurst.txt"), 50.0f, true, true));
		}

	}
}

void Game::OnAddPoints(const Engine::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const Engine::Event& event)
{
	
	if (lives <= 0)
	{
		std::cout << std::get<std::string>(event.data) << std::endl;
		state = eState::GameOver;
	}

}
