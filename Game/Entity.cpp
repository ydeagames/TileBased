#include "Entity.h"

void EntityList::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entities.push_back(entity);
}

void EntityList::Update()
{
	time += Time::deltaTime;
	if (time > 1)
	{
		time -= 1;
		for (auto& entity : entities)
			entity->UpdateTick();
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
	last_pos = next_pos;

	next_pos += Vector2::one;
}

void Entity::Render(const Matrix3& matrix, float partialTicks)
{
	static const Quad quad =
	{ {
			Vector2{ .5f, 0.f },
			Vector2{ 1.f, .5f },
			Vector2{ .5f, 1.f },
			Vector2{ 0.f, .5f },
		} };
	Matrix3 localMatrix = Matrix3::CreateTranslation(Vector2::Lerp(last_pos, next_pos, partialTicks));
	Graphics::DrawQuad(quad * localMatrix * matrix, Colors::Blue, true);
}
