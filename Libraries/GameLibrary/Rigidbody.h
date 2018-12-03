#pragma once
#include "Vec2.h"

class Rigidbody : public Component
{
public:
	Vec2 vel;
	std::vector<int> hit_layers;

public:
	Rigidbody(const Vec2& vel = {}, const std::vector<int>& hit_layers = {})
		: vel(vel)
		, hit_layers(hit_layers) {}

public:
	void AddForce(const Vec2& velocity);

	void Update() override;
};

