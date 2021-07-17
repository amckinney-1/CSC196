#include "Actor.h"
#include "Graphics/Shape.h"

namespace Engine
{
	void Actor::Draw(Core::Graphics& graphics)
	{
		shape->Draw(graphics, transform);
	}
}