#include "Engine.h"

namespace Engine
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<ParticleSystem>());
		// audio system

		for (auto& system : systems)
		{
			system->Startup();
		}

	}

	void Engine::Shutdown()
	{
		for (auto& system : systems)
		{
			system->Shutdown();
		}
	}

	void Engine::Update(float dt)
	{
		for (auto& system : systems)
		{
			system->Update(dt);
		}
	}
}