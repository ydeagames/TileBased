#include "EntityPlacer.h"
#include "Tile.h"
#include "WorldRenderer.h"
#include "GameGlobal.h"
#include "Entity.h"
#include "TileTerrainEditor.h"
#include "EntityLaser.h"

void EntityPlacer::Start()
{
	selected = 0;
	auto terrain = GameObject::Find("Terrain");
	auto tileterrain = terrain->GetComponent<TileTerrain>();
	auto elist = terrain->GetComponent<EntityList>();
	for (auto& pairs : tileterrain->tileRegistry->tiles)
	{
		if (pairs.second->selectable)
		{
			entities.push_back(&pairs.second);
			remaining[pairs.second->id] = pairs.second->count;
		}
	}
	for (auto& chunk : tileterrain->tileMap)
	{
		for (auto& floor : chunk.second.data)
		{
			int iy = 0;
			for (auto& line : floor)
			{
				int ix = 0;
				for (auto& tile : line)
				{
					int unit = tileterrain->tileRegistry->tiles[tile]->unit;
					if (unit >= 0)
						elist->AddEntity(elist->entityRegistry->GetEntity(unit, chunk.first + TileLocalPos{ ix, iy, 1 }));
					ix++;
				}
				iy++;
			}
		}
	}
}

void EntityPlacer::Update()
{
	if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1))
	{
		Vector2 min = Screen::GetBounds().GetMin();
		Vector2 max = Screen::GetBounds().GetMax();

		auto terrain = GameObject::Find("Terrain");
		auto tileterrain = terrain->GetComponent<TileTerrain>();
		auto elist = terrain->GetComponent<EntityList>();
		int total = 0;
		for (auto& pairs : tileterrain->tileRegistry->tiles)
		{
			if (pairs.second->selectable)
				total++;
		}
		float size = 80;
		float width = total * size;

		Vector2 offset = Vector2{ (max.x - width) / 2, max.y - size };

		Vector2 pos = InputManager::GetInstance().mouse->GetPosition();
		Matrix3 matrix =
			Matrix3::CreateScale(Vector2::one * size) *
			Matrix3::CreateTranslation(offset);

		Vector2 pos2 = pos * matrix.Inverse();
		if (0 <= pos2.y && pos2.y < 1)
		{
			int p = static_cast<int>(pos2.x);
			if (0 <= p && p < (int)entities.size())
				selected = p;
		}
		else
		{
			auto& spawner = *entities[selected];

			if (remaining[spawner->id] > 0)
			{
				auto renderer = terrain->GetComponent<WorldRenderer>();
				Vector2 mpos = pos * renderer->GetMatrix().Inverse();
				TilePos tpos = TilePos{ mpos.X(), mpos.Y(), 0 };
				TilePos tpos2 = TilePos{ mpos.X(), mpos.Y(), 1 };
				auto entity = elist->entityRegistry->GetEntity(spawner->unit, tpos);

				auto& tile = tileterrain->tileRegistry->GetTile(tileterrain->GetChunk(tpos).GetTile(tpos));
				auto& tile2 = tileterrain->tileRegistry->GetTile(tileterrain->GetChunk(tpos2).GetTile(tpos2));
				if ((tile->passable && tile2->passable) && (tile->placeable || tile2->placeable))
				{
					auto editor = GameObject::Find("TerrainEditor");
					if (!editor->GetComponent<TileTerrainEditor>()->enabled)
					{
						entity->SetLocationImmediately(tpos);
						elist->AddEntity(entity);
						PlaySoundMem(GameGlobal::GetInstance().se03->GetResource(), DX_PLAYTYPE_BACK);
						remaining[spawner->id]--;
					}
				}
			}
		}
	}

	bool hasRemain = false;
	for (auto& remain : remaining)
	{
		if (remain.second > 0)
		{
			hasRemain = true;
			break;
		}
	}
	if (!hasRemain)
	{
		auto terrain = GameObject::Find("Terrain");
		auto elist = terrain->GetComponent<EntityList>();

		bool hasEntity = false;
		for (auto& entity : elist->entities)
		{
			if (!entity->destroyed && typeid(*entity) != typeid(EntityLaser))
			{
				hasEntity = true;
				break;
			}
		}
		if (!hasEntity)
			SceneManager::GetInstance().RequestScene(SceneID::PLAY);
	}
}

void EntityPlacer::Render()
{
	Vector2 min = Screen::GetBounds().GetMin();
	Vector2 max = Screen::GetBounds().GetMax();

	auto terrain = GameObject::Find("Terrain");
	auto tileterrain = terrain->GetComponent<TileTerrain>();
	auto elist = terrain->GetComponent<EntityList>();
	int total = entities.size();
	float size = 80;
	float width = total * size;

	Vector2 offset = Vector2{ (max.x - width) / 2, max.y - size };
	Bounds bounds = Bounds::CreateFromSize(offset, Vector2{ width, size });
	Quad quad = { bounds };
	Graphics::DrawQuad(quad, Colors::Purple, true);

	Quad identity = Bounds::CreateFromSize(Vector2::zero, Vector2::one);

	for (auto& pentity : entities)
	{
		auto& entity = *pentity;
		if (entity->selectable)
		{
			entity->Render(
				Matrix3::CreateTranslation(Vector2::right * static_cast<float>(entity->unit)) *
				Matrix3::CreateScale(Vector2::one * size) *
				Matrix3::CreateTranslation(offset)
				, nullptr);
			Graphics::DrawQuadString(identity * (
				Matrix3::CreateTranslation(Vector2::right * static_cast<float>(entity->unit)) *
				Matrix3::CreateScale(Vector2::one * size) *
				Matrix3::CreateTranslation(offset)),
				Colors::White,
				GameGlobal::GetInstance().font,
				String::Format("%d", remaining[entity->id]));
		}
	}
	Graphics::DrawQuad(identity * (
		Matrix3::CreateTranslation(Vector2::right * static_cast<float>(selected)) *
		Matrix3::CreateScale(Vector2::one * size) *
		Matrix3::CreateTranslation(offset)
		), Colors::Yellow, false);
}
