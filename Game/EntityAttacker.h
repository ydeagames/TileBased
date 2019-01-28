#pragma once
#include "Entity.h"
#include "TileChunkPos.h"

class EntityAttacker : public Entity
{
private:
	AStar::CoordinateList path;
	AStar::Generator generator;
	TilePos target;

public:
	EntityAttacker(const Texture& te, const TilePos& pos);

public:
	void UpdateTick() override;
};

