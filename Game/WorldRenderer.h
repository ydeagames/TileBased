#pragma once

class WorldRenderer : public Component
{
public:
	Vector2 tileSize = { 48, 48 };

public:
	Matrix3 GetMatrix() const;

public:
	void Render();
};

