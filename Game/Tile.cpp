#include "Tile.h"

void TileTerrain::Render(const Matrix3& world)
{
	for (int iy = 0; iy < 16; iy += TileChunk::ChunkSize)
		for (int ix = 0; ix < 16; ix += TileChunk::ChunkSize)
		{
			GetChunk(ix, iy).Render(tileRegistry, Matrix3::CreateTranslation(Vector2{ ix, iy }*static_cast<float>(TileChunk::ChunkSize)) * world);
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

int& TileChunk::GetTile(int x, int y)
{
	return data[((y % ChunkSize) + ChunkSize) % ChunkSize][((x % ChunkSize) + ChunkSize) % ChunkSize];
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

int& TileTerrain::GetTile(int x, int y)
{
	return GetChunk(x, y).GetTile(x, y);
}

TileChunk& TileTerrain::GetChunk(int x, int y)
{
	return tileMap[y / TileChunk::ChunkSize][x / TileChunk::ChunkSize];
}
