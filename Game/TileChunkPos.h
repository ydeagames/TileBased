#pragma once

class TilePos;
class TileLocalPos;
class ChunkPos;

class TilePos
{
public:
	int x;
	int y;

public:
	TilePos(int x, int y)
		: x(x)
		, y(y) {}

public:
	operator ChunkPos() const;
	operator TileLocalPos() const;
};

class ChunkPos
{
public:
	static const int ChunkSize = 16;

public:
	int x;
	int y;

public:
	ChunkPos(int x, int y)
		: x(x)
		, y(y) {}

public:
	bool operator==(const ChunkPos& rhs) const
	{
		const auto& lhs = *this;
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
	inline bool operator!=(const ChunkPos& rhs) const
	{
		return !(this->operator==(rhs));
	}

public:
	operator TilePos() const;
};

namespace std
{
	template<>
	struct hash<ChunkPos>
	{
		std::size_t operator()(const ChunkPos& key) const
		{
			std::string bytes(reinterpret_cast<const char*>(&key), sizeof(ChunkPos));
			return std::hash<std::string>()(bytes);
		}
	};
}

class TileLocalPos
{
public:
	int x;
	int y;

public:
	TileLocalPos(int x, int y)
		: x(x)
		, y(y) {}
};

TilePos operator+(const ChunkPos& chunkPos, const TileLocalPos& localPos);
