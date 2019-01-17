#pragma once

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

public:
	Tile(const Texture& texture, bool passable = true)
		: texture(texture)
		, passable(passable) {}
	virtual ~Tile() = default;

public:
	void Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const;
};

class TileRegistry
{
public:
	std::unique_ptr<Tile> defaultTile = std::make_unique<Tile>(Texture{ TextureResource::GetMissingTexture() });
	std::unordered_map<int, std::unique_ptr<Tile>> tiles;

public:
	void RegisterTile(int id, std::unique_ptr<Tile>&& tile);

public:
	const Tile& GetTile(int id);
};

class TileChunk
{
public:
	static const int ChunkSize = 16;

public:
	std::array<std::array<int, ChunkSize>, ChunkSize> data;

public:
	int& GetTile(int x, int y);
	void Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3& matrix) const;
};

class TileTerrain : public Component
{
public:
	std::unique_ptr<TileRegistry> tileRegistry;
	std::unordered_map<int, std::unordered_map<int, TileChunk>> tileMap;

public:
	TileTerrain();
	virtual ~TileTerrain() = default;

public:
	int& GetTile(int x, int y);
	TileChunk& GetChunk(int x, int y);

public:
	void Render(const Matrix3& world);
};
