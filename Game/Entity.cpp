#include "Entity.h"

void EntityList::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entities.push_back(entity);
}

void EntityList::Update()
{
	time += Time::deltaTime * speed;
	if (time > 1)
	{
		time -= 1;
		for (auto& entity : entities)
		{
			entity->last_pos = entity->next_pos;
			entity->UpdateTick();
		}
	}
}

void EntityList::Render(const Matrix3& world)
{
	for (auto& entity : entities)
		entity->Render(world, time);
}

void Entity::SetLocation(Vector2 pos)
{
	next_pos = pos;
}

void Entity::SetLocationImmediately(Vector2 pos)
{
	next_pos = pos;
	last_pos = pos;
}

void Entity::UpdateTick()
{
}

void Entity::Render(const Matrix3& matrix, float partialTicks)
{
	Matrix3 localMatrix = Matrix3::CreateTranslation(Vector2::Lerp(last_pos, next_pos, partialTicks));
	static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
	texture.Render(quad * (localMatrix * matrix));
}

void EntityRegistry::RegisterEntity(int id, const std::function<std::shared_ptr<Entity>()>& entity)
{
	entities[id] = entity;
}

std::shared_ptr<Entity> EntityRegistry::GetEntity(int id)
{
	return entities[id]();
}
