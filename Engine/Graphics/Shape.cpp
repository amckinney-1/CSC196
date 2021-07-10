#include "Shape.h"

namespace Engine 
{
	void Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			Engine::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);
			Engine::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			Engine::Vector2 p1 = transform.position + (Vector2::Rotate(points[i], transform.rotation) * transform.scale);
			Engine::Vector2 p2 = transform.position + (Vector2::Rotate(points[i + 1], transform.rotation) * transform.scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}
}
