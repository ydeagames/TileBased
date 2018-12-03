#include "Component.h"

void Component::Initialize(const std::weak_ptr<GameObject>& gameobj)
{
	if (Initialized())
		throw std::logic_error("This component is already initialized");
	gameobject = gameobj;
}

void Component::Finalize()
{
	gameobject.reset();
}

bool Component::Initialized() const
{
	return !gameobject.expired();
}

std::shared_ptr<GameObject> Component::gameObject() const
{
	if (!Initialized())
		throw std::logic_error("コンポーネントが初期化されていません");
	return gameobject.lock();
}
