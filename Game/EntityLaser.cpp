#include "EntityLaser.h"
#include "Tile.h"
#include "GameGlobal.h"

EntityLaser::EntityLaser(const Texture& te, const TilePos& pos, int count)
	: Entity(te, pos)
	, count(count)
{
}

void EntityLaser::UpdateTick()
{
	if (!destroyed && destroying.IsPaused())
	{
		auto terrain = GameObject::Find("Terrain");
		auto elist = terrain->GetComponent<EntityList>();
		for (auto& entity : elist->entities)
		{
			if (&*entity != this && typeid(*entity) != typeid(EntityLaser) && !entity->destroyed && entity->destroying.IsPaused())
			{
				if (entity->last_pos.LengthSquaredTo(last_pos) < 5 * 5)
				{
					entity->destroying.Resume();
					PlaySoundMem(GameGlobal::GetInstance().se02->GetResource(), DX_PLAYTYPE_BACK);
					beams.push_back(std::make_pair(entity->last_pos, Timer{}.Start(.05f)));
					count--;
					if (count <= 0)
						destroying.Resume();
				}
			}
		}
	}
}

void EntityLaser::Render(const Matrix3& matrix, float partialTicks)
{
	Entity::Render(matrix, partialTicks);
	if (!destroyed && destroying.IsPaused())
	{
		for (auto& beam : beams)
		{
			if (!beam.second.IsFinished())
			{
				auto a = last_pos * matrix;
				auto b = beam.first * matrix;
				DrawLineAA(a.x, a.y, b.x, b.y, Colors::Yellow, 2);
			}
		}
	}
}

