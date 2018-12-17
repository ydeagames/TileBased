#pragma once

class GameObject;

class ComponentContainer
{
private:
	std::weak_ptr<GameObject> gameObject;
	std::unordered_multimap<std::type_index, std::shared_ptr<Component>> components;

public:
	ComponentContainer(const std::weak_ptr<GameObject>& gameObject)
		: gameObject(gameObject) {};
	ComponentContainer() = delete;

private:
	ComponentContainer(const ComponentContainer &) = delete;
	ComponentContainer(ComponentContainer &&) = delete;
	ComponentContainer& operator=(ComponentContainer &&) = delete;

public:
	ComponentContainer& operator=(const ComponentContainer& container);

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		components.insert(std::make_pair<std::type_index, std::shared_ptr<Component>>(typeid(T), component));
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		if (components.count(typeid(T)) > 0)
			return std::dynamic_pointer_cast<T>(components.find(typeid(T))->second);
		return nullptr;
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		if (components.count(typeid(T)) > 0)
		{
			auto range = components.equal_range(typeid(T));
			return std::vector<std::shared_ptr<T>>(range.first, range.second);
		}
		return nullptr;
	}

	template<class T>
	bool HasComponent()
	{
		return components.count(typeid(T)) > 0;
	}

public:
	void Start();
	void Update();
	void Render();
};
