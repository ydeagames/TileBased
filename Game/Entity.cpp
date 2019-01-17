#include "Entity.h"

void EntityList::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entities.push_back(entity);
}

void EntityList::Update()
{
	for (auto& entity : entities)
		entity->Update();
}

void EntityList::Render(const Matrix3& world)
{
	for (auto& entity : entities)
		entity->Render(world);
}

void Entity::Update()
{

}

void Entity::Render(const Matrix3& matrix)
{
	static const Quad quad =
	{ {
			Vector2{ .5f, 0.f },
			Vector2{ 1.f, .5f },
			Vector2{ .5f, 1.f },
			Vector2{ 0.f, .5f },
		} };
	Matrix3 localMatrix = Matrix3::CreateTranslation(pos);
	Graphics::DrawQuad(quad * localMatrix * matrix, Colors::Blue, true);
}
