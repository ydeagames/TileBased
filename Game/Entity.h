#pragma once

class Entity
{
public:
	float blocks_per_sec = 4.f;

	Vector2 target_pos;
	Vector2 pos;
	Vector2 vel;

public:
	Entity() = default;
	virtual ~Entity() = default;

public:
	void Update();
	void Render(const Matrix3& matrix);
};

class EntityList : public Component
{
public:
	std::vector<std::shared_ptr<Entity>> entities;

public:
	EntityList() = default;
	virtual ~EntityList() = default;

public:
	void AddEntity(const std::shared_ptr<Entity>& entity);

	void Update();
	void Render(const Matrix3& world);
};
