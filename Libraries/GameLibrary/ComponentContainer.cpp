#include "ComponentContainer.h"

ComponentContainer& ComponentContainer::operator=(const ComponentContainer& container)
{
	components.clear();
	for (auto& entry : container.components)
	{
		entry.second->Finalize();
		components.insert(std::make_pair(entry.first, entry.second));
	}
	return *this;
}

void ComponentContainer::Start()
{
	for (auto& entry : components)
		if (entry.second && !entry.second->Initialized())
		{
			entry.second->Initialize(gameObject);
			entry.second->Start();
		}
}

void ComponentContainer::Update()
{
	for (auto& entry : components)
		if (entry.second)
			entry.second->Update();
}

void ComponentContainer::Render()
{
	for (auto& entry : components)
		if (entry.second)
			entry.second->Render();
}
