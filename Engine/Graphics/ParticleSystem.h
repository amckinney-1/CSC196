#pragma once
#include "Base/System.h"

namespace Engine
{
	class ParticleSystem : public System
	{

	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float);
	};

	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		float lifetime;
		bool isActive;

		static bool isNotActive(Particle )

	}
}