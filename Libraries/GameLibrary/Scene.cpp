#include "Scene.h"

void Scene::Update()
{
	for (auto& object : objects)
		object.second->Start();

	for (auto itr = objects.begin(); itr != objects.end();)
	{
		itr->second->Update();
		if (itr->second->IsDestroyed())
		{
			itr = objects.erase(itr);
			continue;
		}
		++itr;
	}
	for (auto& layer : layers)
		layer.erase(std::remove_if(layer.begin(), layer.end(), [](std::weak_ptr<GameObject>& obj)->bool { return obj.expired() || obj.lock()->IsDestroyed(); }), layer.end());
}

void Scene::Render()
{
	for (auto& layer : layers)
		for (auto& wobject : layer)
			if (auto object = wobject.lock())
				if (object && !object->IsDestroyed())
					object->Render();
}
