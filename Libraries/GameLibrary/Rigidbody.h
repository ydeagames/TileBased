#pragma once
#include "Vector2.h"

class Rigidbody : public Component
{
public:
	Vector2 vel;
	std::vector<int> hit_layers;

public:
	Rigidbody(const Vector2& vel = {}, const std::vector<int>& hit_layers = {})
		: vel(vel)
		, hit_layers(hit_layers) {}

public:
	void AddForce(const Vector2& velocity);

	void Update() override;
};

