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
	if (!destroyed)
	{
		Matrix3 localMatrix = Matrix3::CreateTranslation(Vector2::Lerp(last_pos, next_pos, partialTicks));
		static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
		if (!destroying.IsPaused())
		{
			static Texture explosion = Texture{
				std::vector<std::shared_ptr<TextureResource>>{
					std::make_shared<TextureResource>("explosion1.png"),
					std::make_shared<TextureResource>("explosion2.png"),
					std::make_shared<TextureResource>("explosion3.png"),
				}, 1.f/3, false
			};
			Graphics::DrawQuadGraph(quad * (localMatrix * matrix), explosion.GetFrame(destroying.GetProgress()));
			if (destroying.IsFinished())
				destroyed = true;
		}
		else
			texture.Render(quad * (localMatrix * matrix));
	}
}

void EntityRegistry::RegisterEntity(int id, const std::function<std::shared_ptr<Entity>(const TilePos&)>& entity)
{
	entities[id] = entity;
}

std::shared_ptr<Entity> EntityRegistry::GetEntity(int id, const TilePos& pos)
{
	return entities[id](pos);
}
