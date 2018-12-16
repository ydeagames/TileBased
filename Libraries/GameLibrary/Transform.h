#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Matrix.h"

class Transform final : public Component
{
public:
	Vec2 position;				// <テクスチャ>
	float rotation;				// <回転>
	Vec2 scale;					// <スケール>

public:
	Transform(const Vec2& position, float rotation, const Vec2& scale);
	Transform();

public:
	Matrix3 GetMatrix() const;
};
