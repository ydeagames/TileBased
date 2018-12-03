#pragma once
#include "Vec2.h"
#include "Shape.h"

namespace Graphics
{
	// <�x�N�g����`��>
	int DrawVector(const Vec2& vector, const Vec2& base, Color color, float Thickness = 1.f);

	// ��]������
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
}