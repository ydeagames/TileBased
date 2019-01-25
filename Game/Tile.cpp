#include "Tile.h"

void TileTerrain::Render(const Matrix3& world)
{
	for (int iy = 0; iy < 16 / TileChunk::ChunkSize; iy++)
		for (int ix = 0; ix < 16 / TileChunk::ChunkSize; ix++)
		{
			GetChunk({ ix, iy }).Render(
				tileRegistry,
				Matrix3::CreateTranslation(Vector2{ ix, iy }*static_cast<float>(TileChunk::ChunkSize)) * world);
		}
}

void Tile::Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const
{
	static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
	texture.Render(quad * matrix);
}

const Tile& TileRegistry::GetTile(int id)
{
	auto& tile = tiles[id];
	if (tile)
		return *tile;
	return *defaultTile;
}

void TileRegistry::RegisterTile(int id, std::unique_ptr<Tile>&& tile)
{
	tiles[id] = std::move(tile);
}

int& TileChunk::GetTile(const TileLocalPos& localPos)
{
	return data[localPos.y][localPos.x];
}

void TileChunk::Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3 & matrix) const
{
	int iy = 0;
	for (auto& line : data)
	{
		int ix = 0;
		for (auto& tile : line)
		{
			registry->tiles[tile]->Render(Matrix3::CreateTranslation(Vector2{ ix,iy }) * matrix, nullptr);
			ix++;
		}
		iy++;
	}
}

TileTerrain::TileTerrain()
	: tileRegistry(std::make_unique<TileRegistry>())
{
}

TileChunk& TileTerrain::GetChunk(const ChunkPos& chunkPos)
{
	return tileMap[chunkPos];
}

TileChunk TileChunkLoader::Load(const ChunkPos& chunkPos) const
{
	//LoadSoftImage(String::Format("%s/r.%d.%d.png", savesDir, chunkPos.x, chunkPos.y));
	return TileChunk();
}

void TileChunkLoader::Save(const ChunkPos & chunkPos, const TileChunk& chunk) const
{
}
