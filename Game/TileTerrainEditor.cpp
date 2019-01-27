#include "TileTerrainEditor.h"
#include "Tile.h"
#include "WorldRenderer.h"
#include "GameGlobal.h"

void TileTerrainEditor::Start()
{
	selected = 0;
	enabled = false;
}

void TileTerrainEditor::Update()
{
	if (InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_F3))
		enabled = !enabled;
	if (enabled)
	{
		if (InputManager::GetInstance().mouse->GetButton(MOUSE_INPUT_1))
		{
			Vector2 min = Screen::GetBounds().GetMin();
			Vector2 max = Screen::GetBounds().GetMax();
			Vector2 offset = Vector2{ max.x - 40, min.y };

			Vector2 pos = InputManager::GetInstance().mouse->GetPosition();
			Matrix3 matrix =
				Matrix3::CreateScale(Vector2::one * 40.f) *
				Matrix3::CreateTranslation(offset);

			auto terrain = GameObject::Find("Terrain");
			auto tileterrain = terrain->GetComponent<TileTerrain>();

			Vector2 pos2 = pos * matrix.Inverse();
			if (0 <= pos2.x && pos2.x < 1)
			{
				if (tileterrain->tileRegistry->tiles.count(static_cast<int>(pos2.y)) > 0)
					selected = static_cast<int>(pos2.y);
			}
			else
			{
				auto& tile = tileterrain->tileRegistry->GetTile(selected);

				auto renderer = terrain->GetComponent<WorldRenderer>();
				Vector2 mpos = pos * renderer->GetMatrix().Inverse();
				TilePos tpos = TilePos{ mpos.X(), mpos.Y(), tile->floor };
				tileterrain->GetChunk(tpos).GetTile(tpos) = tile->id;
			}
		}
		if (InputManager::GetInstance().key->GetButton(KEY_INPUT_LCONTROL) && InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_S))
		{
			auto terrain = GameObject::Find("Terrain");
			auto tileterrain = terrain->GetComponent<TileTerrain>();
			for (auto& chunk : tileterrain->tileMap)
				tileterrain->SaveChunk(chunk.first);
		}
	}
}

void TileTerrainEditor::Render()
{
	if (enabled)
	{
		Vector2 min = Screen::GetBounds().GetMin();
		Vector2 max = Screen::GetBounds().GetMax();
		Vector2 offset = Vector2{ max.x - 50, min.y };
		Bounds bounds = Bounds::CreateFromPosition(offset, max);
		Quad quad = { bounds };
		Graphics::DrawQuad(quad, Colors::Purple, true);

		Quad identity = Bounds::CreateFromSize(Vector2::zero, Vector2::one);

		auto tileterrain = GameObject::Find("Terrain")->GetComponent<TileTerrain>();
		for (auto& pairs : tileterrain->tileRegistry->tiles)
		{
			Graphics::DrawQuad(identity * (
				Matrix3::CreateTranslation(Vector2::down * static_cast<float>(pairs.first)) *
				Matrix3::CreateScale(Vector2{ 10, 40 }) *
				Matrix3::CreateTranslation(offset)
				), pairs.second->floor == 0 ? Colors::Blue : Colors::Red, true);
			pairs.second->Render(
				Matrix3::CreateTranslation(Vector2::down * static_cast<float>(pairs.first)) *
				Matrix3::CreateScale(Vector2::one * 40.f) *
				Matrix3::CreateTranslation(Vector2::right * 10) *
				Matrix3::CreateTranslation(offset)
				, nullptr);
		}
		Graphics::DrawQuad(identity * (
			Matrix3::CreateTranslation(Vector2::down * static_cast<float>(selected)) *
			Matrix3::CreateScale(Vector2{ 50, 40 }) *
			Matrix3::CreateTranslation(offset)
			), Colors::Yellow, false);
		if (tileterrain->tileRegistry->tiles.count(selected) > 0)
			Graphics::DrawQuadString(identity * (
				Matrix3::CreateTranslation(Vector2::down * static_cast<float>(selected)) *
				Matrix3::CreateScale(Vector2::one * 40.f) *
				Matrix3::CreateTranslation(offset + Vector2::left * 320)),
				Colors::White,
				GameGlobal::GetInstance().font,
				String::Format(tileterrain->tileRegistry->GetTile(selected)->name));
	}
}
