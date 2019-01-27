#include "EntityPlacer.h"
#include "Tile.h"
#include "WorldRenderer.h"
#include "GameGlobal.h"
#include "Entity.h"
#include "TileTerrainEditor.h"

void EntityPlacer::Start()
{
	selected = 0;
	auto terrain = GameObject::Find("Terrain");
	auto tileterrain = terrain->GetComponent<TileTerrain>();
	for (auto& pairs : tileterrain->tileRegistry->tiles)
	{
		if (pairs.second->unit >= 0)
			entities.push_back(&pairs.second);
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
			if (pairs.second->unit >= 0)
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

			auto entity = elist->entityRegistry->GetEntity(spawner->unit);

			auto renderer = terrain->GetComponent<WorldRenderer>();
			Vector2 mpos = pos * renderer->GetMatrix().Inverse();
			TilePos tpos = TilePos{ mpos.X(), mpos.Y(), 0 };
			auto& tile = tileterrain->tileRegistry->GetTile(tileterrain->GetChunk(tpos).GetTile(tpos));
			if (tile->passable && tile->placeable)
			{
				auto editor = GameObject::Find("TerrainEditor");
				if (!editor->GetComponent<TileTerrainEditor>()->enabled)
				{
					entity->SetLocationImmediately(tpos);
					elist->AddEntity(entity);
					PlaySoundMem(GameGlobal::GetInstance().se03->GetResource(), DX_PLAYTYPE_BACK);
				}
			}
		}
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
		if (entity->unit >= 0)
			entity->Render(
				Matrix3::CreateTranslation(Vector2::right * static_cast<float>(entity->unit)) *
				Matrix3::CreateScale(Vector2::one * size) *
				Matrix3::CreateTranslation(offset)
				, nullptr);
	}
	Graphics::DrawQuad(identity * (
		Matrix3::CreateTranslation(Vector2::right * static_cast<float>(selected)) *
		Matrix3::CreateScale(Vector2::one * size) *
		Matrix3::CreateTranslation(offset)
		), Colors::Yellow, false);
}
