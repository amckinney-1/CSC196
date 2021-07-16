#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "core.h"
#include <memory>

namespace Engine
{
	class Shape;
	class Scene;

	class Actor : public Object
	{
	public:
		Actor(const Transform& transform, std::shared_ptr<Shape> shape) : transform{ transform }, shape{ shape } {};

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

	public:
		bool destroy{ false };

		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{ nullptr };

	};
}