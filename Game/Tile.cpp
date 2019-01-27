#include "Tile.h"

void TileTerrain::Render(const Matrix3& world)
{
	for (auto& chunk : tileMap)
	{
		chunk.second.Render(
			tileRegistry,
			Matrix3::CreateTranslation((Vector2)(TilePos)chunk.first)
			* world);
	}
}

void Tile::Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const
{
	static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
	texture.Render(quad * matrix);
}

const std::unique_ptr<Tile>& TileRegistry::GetTile(int id)
{
	auto& tile = tiles[id];
	if (tile)
		return tile;
	return defaultTile;
}

void TileRegistry::RegisterTile(int id, std::unique_ptr<Tile>&& tile)
{
	tiles[id] = std::move(tile);
}

int& TileChunk::GetTile(const TileLocalPos& localPos)
{
	return data[localPos.z][localPos.y][localPos.x];
}

const int& TileChunk::GetTile(const TileLocalPos& localPos) const
{
	return data[localPos.z][localPos.y][localPos.x];
}

void TileChunk::Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3 & matrix) const
{
	for (auto& floor : data)
	{
		int iy = 0;
		for (auto& line : floor)
		{
			int ix = 0;
			for (auto& tile : line)
			{
				registry->tiles[tile]->Render(Matrix3::CreateTranslation(Vector2{ ix, iy }) * matrix, nullptr);
				ix++;
			}
			iy++;
		}
	}
}

TileTerrain::TileTerrain()
	: tileRegistry(std::make_unique<TileRegistry>())
	, loader("Resources/Saves")
{
}

TileChunk& TileTerrain::GetChunk(const ChunkPos& chunkPos)
{
	return tileMap[chunkPos];
}

const TileChunk& TileTerrain::GetChunk(const ChunkPos& chunkPos) const
{
	return tileMap.at(chunkPos);
}

void TileTerrain::LoadChunk(const ChunkPos& chunkPos)
{
	GetChunk(chunkPos) = loader.Load(chunkPos);
}

void TileTerrain::SaveChunk(const ChunkPos& chunkPos) const
{
	loader.Save(chunkPos, GetChunk(chunkPos));
}

TileChunkLoader::TileChunkLoader(const std::string & savesDir)
	: savesDir(savesDir)
{
	CreateDirectoryA(savesDir.c_str(), nullptr);
}

TileChunk TileChunkLoader::Load(const ChunkPos& chunkPos) const
{
	TileChunk result;
	for (int i = 0; i < TileChunk::ChunkHeight; i++)
	{
		HGRP data = LoadSoftImage(String::Format("%s/r.%d.%d.%d.bmp", savesDir.c_str(), chunkPos.x, chunkPos.y, i).operator LPCSTR());
		if (data != -1)
		{
			for (int iy = 0; iy < ChunkPos::ChunkSize; iy++)
				for (int ix = 0; ix < ChunkPos::ChunkSize; ix++)
				{
					int pixel = GetPixelPalCodeSoftImage(data, ix, iy);
					result.GetTile(TileLocalPos{ ix, iy, i }) = pixel;
				}
			DeleteSoftImage(data);
		}
	}
	return result;
}

void TileChunkLoader::Save(const ChunkPos& chunkPos, const TileChunk& chunk) const
{
	for (int i = 0; i < TileChunk::ChunkHeight; i++)
	{
		HGRP data = MakePAL8ColorSoftImage(ChunkPos::ChunkSize, ChunkPos::ChunkSize, false);
		for (int iy = 0; iy < ChunkPos::ChunkSize; iy++)
			for (int ix = 0; ix < ChunkPos::ChunkSize; ix++)
				DrawPixelPalCodeSoftImage(data, ix, iy, chunk.GetTile(TileLocalPos{ ix, iy, i }));
		auto path = String::Format("%s/r.%d.%d.%d.bmp", savesDir.c_str(), chunkPos.x, chunkPos.y, i);
		int err = SaveSoftImageToBmp(path, data);
		if (err == -1)
			throw std::exception("IOException: cannot save map.");
		DeleteSoftImage(data);
	}
}

TileLoader::TileLoader(const std::string& blocksDir)
	: blocksDir(blocksDir)
{
}

std::unique_ptr<Tile> TileLoader::Load(const std::string& name) const
{
	auto path = String::Format("%s/%s.json", blocksDir.c_str(), name.c_str());
	std::ifstream t(path.operator std::string());
	std::string str = {
		std::istreambuf_iterator<char>(t),
		std::istreambuf_iterator<char>()
	};

	json::Json data = json::Json::Load(str);

	auto tilename = data["name"].ToString();
	auto passable = data["passable"].ToBool();
	auto texture = data["texture"].ToString();
	auto floor = data["floor"].ToInt();
	auto id = data["id"].ToInt();
	auto placeable = data["placeable"].ToBool();
	auto unit = data["unit"].ToInt();

	auto tiletexture = std::make_shared<TextureResource>(texture);
	auto tile = std::make_unique<Tile>(tiletexture, passable);
	tile->name = tilename;
	tile->floor = static_cast<int>(floor);
	tile->id = id;
	tile->placeable = placeable;
	tile->unit = static_cast<int>(unit);

	return tile;
}

std::vector<std::unique_ptr<Tile>> TileLoader::LoadAll() const
{
	std::vector<std::unique_ptr<Tile>> result;
	for (const auto& entry : std::experimental::filesystem::directory_iterator(blocksDir))
	{
		if (entry.path().extension().string() == ".json")
			result.push_back(Load(entry.path().stem().string()));
	}
	return result;
}
