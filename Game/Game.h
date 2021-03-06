#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateLevelStart(float dt);

	void OnAddPoints(const Engine::Event& event);
	void OnPlayerDead(const Engine::Event& event);

public:
	std::unique_ptr<Engine::Engine> engine;
	std::unique_ptr<Engine::Scene> scene;

private:
	eState state{ eState::Title };
	float stateTimer{ 0.0f };
	float levelTimer{ 0.0f };

	size_t score{ 0 };
	size_t lives{ 0 };
	size_t level{ 0 };

};