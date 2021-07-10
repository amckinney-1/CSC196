#pragma once
#include "Vector2.h"

namespace Engine
{
	struct Transform {
		Vector2 position;
		float rotation{ 0 };
		float scale{ 1 };

		Transform() {}
		Transform(const Vector2& position, float rotation = 0, float scale = 0) : position{position}, rotation{rotation}, scale{scale} {}
	};
}