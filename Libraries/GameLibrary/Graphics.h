#pragma once
#include "Vector2.h"
#include "Shape.h"

namespace Graphics
{
	// <ƒxƒNƒgƒ‹‚ð•`‰æ>
	int DrawVector(const Vector2& vector, const Vector2& base, Color color, float Thickness = 1.f);

	// ‰ñ“]’¼•û‘Ì
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
}