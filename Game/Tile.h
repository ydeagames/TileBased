#pragma once
#include "TileChunkPos.h"

class TileEntity
{
public:

public:
	TileEntity() = default;
	virtual ~TileEntity() = default;

public:
};

class Tile
{
public:
	Texture texture;
	bool passable;
	std::string name = "none";
	int floor = 0;
	int id = 0;

public:
	Tile(const Texture& texture, bool passable = true)
		: texture(texture)
		, passable(passable) {}
	virtual ~Tile() = default;

public:
	void Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const;
};

class TileLoader
{
private:
	const std::string blocksDir;

public:
	TileLoader(const std::string& blocksDir);

public:
	std::unique_ptr<Tile> Load(const std::string& name) const;
	std::vector<std::unique_ptr<Tile>> LoadAll() const;
};

class TileRegistry
{
public:
	std::unique_ptr<Tile> defaultTile = std::make_unique<Tile>(Texture{ TextureResource::GetMissingTexture() });
	std::unordered_map<int, std::unique_ptr<Tile>> tiles;

public:
	void RegisterTile(int id, std::unique_ptr<Tile>&& tile);

public:
	const std::unique_ptr<Tile>& GetTile(int id);
};

class TileChunkLoader;

class TileChunk
{
public:
	static const int ChunkHeight = 2;
	static const std::unique_ptr<TileChunkLoader> loader;

public:
	std::array<std::array<std::array<int, ChunkPos::ChunkSize>, ChunkPos::ChunkSize>, ChunkHeight> data;

public:
	int& GetTile(const TileLocalPos& localPos);
	const int & GetTile(const TileLocalPos & localPos) const;
	void Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3& matrix) const;
};

class TileChunkLoader
{
private:
	const std::string savesDir;

public:
	TileChunkLoader(const std::string& savesDir);

public:
	TileChunk Load(const ChunkPos& chunkPos) const;
	void Save(const ChunkPos& chunkPos, const TileChunk& chunk) const;
};

class TileTerrain : public Component
{
public:
	std::unique_ptr<TileRegistry> tileRegistry;
	std::unordered_map<ChunkPos, TileChunk> tileMap;
	TileChunkLoader loader;

public:
	TileTerrain();
	virtual ~TileTerrain() = default;

public:
	TileChunk& GetChunk(const ChunkPos& chunkPos);
	const TileChunk& GetChunk(const ChunkPos& chunkPos) const;
	void LoadChunk(const ChunkPos& chunkPos);
	void SaveChunk(const ChunkPos& chunkPos) const;

public:
	void Render(const Matrix3& world);
};
