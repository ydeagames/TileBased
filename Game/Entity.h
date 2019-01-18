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

class EntityList : public Component
{
public:
	constexpr static float speed = .8f;

public:
	std::vector<std::shared_ptr<Entity>> entities;
	float time;

public:
	EntityList() = default;
	virtual ~EntityList() = default;

public:
	void AddEntity(const std::shared_ptr<Entity>& entity);

	void Update();
	void Render(const Matrix3& world);
};
