#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Matrix.h"

class Transform final : public Component
{
public:
	Vector2 position;				// <テクスチャ>
	float rotation;				// <回転>
	Vector2 scale;					// <スケール>

public:
	Transform(const Vector2& position, float rotation, const Vector2& scale);
	Transform();

public:
	Matrix3 GetMatrix() const;
};
