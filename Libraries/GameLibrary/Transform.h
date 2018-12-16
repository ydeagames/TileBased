#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Matrix.h"

class Transform final : public Component
{
public:
	Vector2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	Vector2 scale;					// <�X�P�[��>

public:
	Transform(const Vector2& position, float rotation, const Vector2& scale);
	Transform();

public:
	Matrix3 GetMatrix() const;
};
