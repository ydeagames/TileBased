#include "EntityAttacker.h"
#include "Tile.h"

EntityAttacker::EntityAttacker(const Texture& te)
	: Entity(te)
	, target({ 0, 0, 0 })
{
	auto terrain = GameObject::Find("Terrain");
	auto tileterrain = terrain->GetComponent<TileTerrain>();

	int minX = 0, minY = 0, maxX = 0, maxY = 0;
	for (auto& chunk : tileterrain->tileMap)
	{
		minX = std::min(minX, chunk.first.x);
		minY = std::min(minY, chunk.first.y);
		maxX = std::max(maxX, chunk.first.x);
		maxY = std::max(maxY, chunk.first.y);
	}

	// Set 2d map size.
	generator.setWorldSize({ (maxX - minX + 1) * ChunkPos::ChunkSize, (maxY - minY + 1) * ChunkPos::ChunkSize });
	// You can use a few heuristics : manhattan, euclidean or octagonal.
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(true);

	for (auto& chunk : tileterrain->tileMap)
	{
		int iy = 0;
		for (auto& line : chunk.second.data[1])
		{
			int ix = 0;
			for (auto& tileid : line)
			{
				TilePos pos = chunk.first + TileLocalPos{ ix, iy, 0 };
				auto& tile = tileterrain->tileRegistry->GetTile(tileid);
				if (tile->id == 8)
					target = pos;
				else if (!tile->passable)
					generator.addCollision({ pos.x, pos.y });
				ix++;
			}
			iy++;
		}
	}
}

void EntityAttacker::UpdateTick()
{
	// This method returns vector of coordinates from target to source.
	auto path = generator.findPath({ last_pos.X(), last_pos.Y() }, { target.x, target.y });
	if (path.size() > 1)
	{
		auto& last = path.at(path.size() - 2);
		SetLocation({ last.x, last.y });
	}
}
