#include "Shape.h"
#include <fstream>

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

	bool Shape::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			stream >> color;
			
			//read number of points
			std::string line;
			std::getline(stream, line);
			size_t size = std::stoi(line);

			for (size_t i = 0; i < size; i++)
			{
				Engine::Vector2 point;
				stream >> point;

				points.push_back(point);
			}

			Engine::Vector2 point;
			stream >> point;
		}

		return success;
	}
}
