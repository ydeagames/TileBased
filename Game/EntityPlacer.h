#pragma once
#include "Tile.h"

class EntityPlacer: public Component
{
public:
	int selected;
	std::vector<std::unique_ptr<Tile>*> entities;
	std::unordered_map<int, int> remaining;

public:
	void Start() override;
	void Update() override;
	void Render() override;
};

