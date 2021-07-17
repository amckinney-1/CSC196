#include "Scene.h"
#include "Actor.h"

namespace Engine
{
	using namespace Engine;
	void Scene::Update(float dt)
	{
		// add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		// update actors
		for (auto& actor : actors)
		{
			actor->Update(dt);
		}

		// check collisions
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();
				if (distance < 10)
				{
					actors[i]->OnCollision(actors[j].get());
					actors[j]->OnCollision(actors[i].get());
				}
			}
		}

		// destroy actor
		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy)
			{
				iter = actors.erase(iter);
			}
			else
			{
			iter++;

			}

		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (auto& actor : actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;

		Scene::newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor)
	{

	}

	void Scene::RemoveAllActors()
	{
		actors.clear();
	}
}