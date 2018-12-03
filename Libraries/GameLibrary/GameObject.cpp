#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

GameObject::GameObject(const std::string& name, int layer, const std::string& tag)
	: name(name)
	, layer(layer)
	, tag(tag)
	, components(nullptr)
	, destroyed(false)
{
}

void GameObject::Initialize()
{
	components = std::make_unique<ComponentContainer>(shared_from_this());
	AddComponent<Transform>(std::make_shared<Transform>());
}

std::shared_ptr<Transform> GameObject::transform()
{
	return GetComponent<Transform>();
}

void GameObject::Start()
{
	components->Start();
}

void GameObject::Update()
{
	components->Update();
}

void GameObject::Render()
{
	components->Render();
}

void GameObject::Destroy()
{
	destroyed = true;
}

bool GameObject::IsDestroyed()
{
	return destroyed;
}

std::shared_ptr<GameObject> GameObject::CreatePrefab(const std::string& name, int layer, const std::string& tag)
{
	auto obj = std::shared_ptr<GameObject>(new GameObject(name, layer, tag));
	obj->Initialize();
	return obj;
}

std::shared_ptr<GameObject> GameObject::Create(const std::string& name, int layer, const std::string& tag)
{
	auto object = CreatePrefab(name, layer, tag);
	SceneManager::GetInstance().AddObject(object);
	return object;
}

std::shared_ptr<GameObject> GameObject::Find(const std::string& name)
{
	auto range = SceneManager::GetInstance().GetActiveScene()->objects.equal_range(name);
	for (auto it = range.first; it != range.second; ++it)
	{
		if (!it->second->IsDestroyed())
			return it->second;
	}
	return nullptr;
}

std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
{
	auto& mmap = SceneManager::GetInstance().GetActiveScene()->tags;
	auto range = mmap.equal_range(tag);
	for (auto it = range.first; it != range.second;)
	{
		auto obj = it->second.lock();
		if (obj && !obj->IsDestroyed())
			return obj;
		else
		{
			it = mmap.erase(it);
			continue;
		}
		++it;
	}
	return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
{
	std::vector<std::shared_ptr<GameObject>> result;
	auto& mmap = SceneManager::GetInstance().GetActiveScene()->tags;
	auto range = mmap.equal_range(tag);
	for (auto it = range.first; it != range.second;)
	{
		auto obj = it->second.lock();
		if (obj && !obj->IsDestroyed())
			result.push_back(obj);
		else
		{
			it = mmap.erase(it);
			continue;
		}
		++it;
	}
	return result;
}

std::vector<std::weak_ptr<GameObject>>& GameObject::FindGameObjectsWithLayer(int layer)
{
	if (layer < 0 && Scene::MAX_LAYERS <= layer)
		throw std::invalid_argument("Invalid layer number");
	return SceneManager::GetInstance().GetActiveScene()->layers[layer];
}

std::shared_ptr<GameObject> GameObject::Instantiate(const std::shared_ptr<GameObject>& originalObject)
{
	if (originalObject->IsDestroyed())
		throw std::invalid_argument("Cannot instantiate destroyed object");
	auto object = Create(originalObject->name + "(Clone)");
	*object->components = *originalObject->components;
	return object;
}
