#pragma once
#include "Entity.h"
#include "TileChunkPos.h"

class EntityLaser : public Entity
{
public:
	std::vector<std::pair<Vector2, Timer>> beams;
	int count;

public:
	EntityLaser(const Texture& te, const TilePos& pos, int count = 2);

public:
	void UpdateTick() override;
	void Render(const Matrix3& matrix, float partialTicks) override;
};

