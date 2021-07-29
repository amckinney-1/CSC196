#include "Actor.h"
#include "Graphics/Shape.h"
#include <algorithm>

namespace Engine
{
	void Actor::Update(float dt)
	{
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) { child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape)
		{
			shape->Draw(graphics, transform);
		}

		std::for_each(children.begin(), children.end(), [graphics](auto& child) mutable { if(child->shape) child->shape->Draw(graphics, child->transform); });
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale;
	}

	void Actor::AddChild(std::unique_ptr<Actor> child)
	{
		child->parent = this;
		children.push_back(std::move(child));
	}
}