#pragma once
#include "Entity.h"
#include "TileChunkPos.h"

class EntityBomb : public Entity
{
public:
	AStar::CoordinateList path;
	AStar::Generator generator;
	TilePos target;

public:
	EntityBomb(const Texture& te, const TilePos& pos);

public:
	void UpdateTick() override;
};

