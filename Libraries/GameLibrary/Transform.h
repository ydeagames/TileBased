#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Matrix.h"

class Transform final : public Component
{
public:
	Vec2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	Vec2 scale;					// <�X�P�[��>

public:
	Transform(const Vec2& position, float rotation, const Vec2& scale);
	Transform();

public:
	Matrix3 GetMatrix() const;
};
