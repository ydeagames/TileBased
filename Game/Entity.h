#pragma once

class Entity
{
public:
	float blocks_per_sec = 4.f;

	Vector2 last_pos;
	Vector2 next_pos;

public:
	Entity() = default;
	virtual ~Entity() = default;

public:
	void SetLocation(Vector2 pos);
	void SetLocationImmediately(Vector2 pos);
	void UpdateTick();
	void Render(const Matrix3& matrix, float partialTicks);
};

class EntityRegistry
{
public:
	std::unordered_map<int, std::function<std::shared_ptr<Entity>()>> entities;

public:
	void RegisterEntity(int id, const std::function<std::shared_ptr<Entity>()>& entity);

public:
	std::shared_ptr<Entity> GetEntity(int id);
};

class EntityList : public Component
{
public:
	constexpr static float speed = .8f;

public:
	std::vector<std::shared_ptr<Entity>> entities;
	std::unique_ptr<EntityRegistry> entityRegistry;
	float time;

public:
	EntityList()
		: entityRegistry(std::make_unique<EntityRegistry>()) {}
	virtual ~EntityList() = default;

public:
	void AddEntity(const std::shared_ptr<Entity>& entity);

	void Update();
	void Render(const Matrix3& world);
};
