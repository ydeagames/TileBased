#pragma once

class GameObject final : public std::enable_shared_from_this<GameObject>
{
public:
	const std::string name;
	const std::string tag;
	const int layer;

private:
	std::unique_ptr<ComponentContainer> components;
	bool destroyed;

public:
	std::shared_ptr<Transform> transform();

private:
	GameObject(const std::string& name, int layer, const std::string& tag);
	GameObject(const GameObject &) = delete;
	GameObject& operator=(const GameObject &) = delete;
	GameObject(GameObject &&) = delete;
	GameObject& operator=(GameObject &&) = delete;
	void Initialize();

public:
	template<class T>
	auto AddComponent(const std::shared_ptr<T>& component)
	{
		components->AddComponent(component);
		return component;
	}

	template<class T, typename... Args>
	auto AddNewComponent(Args&&... args)
	{
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		AddComponent<T>(component);
		return component;
	}

	template<class TypeClass, class CreateClass, typename... Args>
	auto AddNewComponentAs(Args&&... args)
	{
		auto component = std::make_shared<CreateClass>(std::forward<Args>(args)...);
		AddComponent<TypeClass>(component);
		AddComponent<CreateClass>(component);
		return component;
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return components->GetComponent<T>();
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		return components->GetComponents<T>();
	}

	template<class T>
	bool HasComponent()
	{
		return components->HasComponent<T>();
	}

public:
	void Start();
	void Update();
	void Render();

	void Destroy();
	bool IsDestroyed();

public:
	static std::shared_ptr<GameObject> CreatePrefab(const std::string& name = "New Game Object", int layer = 0, const std::string& tag = "Untagged");
	static std::shared_ptr<GameObject> Create(const std::string& name = "New Game Object", int layer = 0, const std::string& tag = "Untagged");
	static std::shared_ptr<GameObject> Find(const std::string& name);
	static std::shared_ptr<GameObject> FindWithTag(const std::string & tag);
	static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTag(const std::string & tag);
	static std::vector<std::weak_ptr<GameObject>>& FindGameObjectsWithLayer(int layer);
	static std::shared_ptr<GameObject> Instantiate(const std::shared_ptr<GameObject>& originalObject);
};

