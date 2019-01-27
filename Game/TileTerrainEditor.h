#pragma once

class TileTerrainEditor: public Component
{
public:
	int selected;
	bool enabled;

public:
	void Start() override;
	void Update() override;
	void Render() override;
};

