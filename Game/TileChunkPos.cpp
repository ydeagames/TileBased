#include "TileChunkPos.h"

TilePos::operator ChunkPos() const
{
	return{
		static_cast<int>(std::floor(static_cast<float>(x) / ChunkPos::ChunkSize)),
		static_cast<int>(std::floor(static_cast<float>(y) / ChunkPos::ChunkSize)),
	};
}

TilePos::operator TileLocalPos() const
{
	return{
		((x % ChunkPos::ChunkSize) + ChunkPos::ChunkSize) % ChunkPos::ChunkSize,
		((y % ChunkPos::ChunkSize) + ChunkPos::ChunkSize) % ChunkPos::ChunkSize,
		z,
	};
}

TilePos::operator Vector2() const
{
	return{ x, y };
}

ChunkPos::operator TilePos() const
{
	return{ x * ChunkSize, y * ChunkSize, 0 };
}

TilePos operator+(const ChunkPos& chunkPos, const TileLocalPos& localPos)
{
	return{ chunkPos.x * ChunkPos::ChunkSize + localPos.x, chunkPos.y * ChunkPos::ChunkSize + localPos.y, localPos.z };
}
