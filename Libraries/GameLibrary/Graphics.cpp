#include "Graphics.h"
#define DX(exp) if (exp) { return -1; }

namespace Graphics
{
	// <ƒxƒNƒgƒ‹‚ð•`‰æ>
	int DrawVector(const Vector2& vector, const Vector2& base, Color color, float Thickness)
	{
		float arrow_length = 10 + Thickness * vector.Length()*.125f;
		float arrow_rota = vector.Angle();
		float arrow_rota1 = arrow_rota + MathUtils::ToRadians(-150);
		float arrow_rota2 = arrow_rota + MathUtils::ToRadians(150);
		DX(DrawLineAA(base.x, base.y, base.x + vector.x, base.y + vector.y, color, Thickness));
		DX(DrawLineAA(base.x + vector.x, base.y + vector.y, base.x + vector.x + (arrow_length * std::cosf(arrow_rota1)),
			base.y + vector.y + (arrow_length * std::sinf(arrow_rota1)), color, Thickness));
		DX(DrawLineAA(base.x + vector.x, base.y + vector.y, base.x + vector.x + (arrow_length * std::cosf(arrow_rota2)),
			base.y + vector.y + (arrow_length * std::sinf(arrow_rota2)), color, Thickness));
		return 0;
	}

	// ‰ñ“]’¼•û‘Ì
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness)
	{
		Vector2 vertex[4];
		for (int i = 0; i < 4; ++i) {
			Vector2 c = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
			vertex[i] = (box.size / 2 * c).Rotate(box.angle) + box.center;
		}

		DX(DrawQuadrangleAA(vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y, vertex[2].x, vertex[2].y, vertex[3].x, vertex[3].y, Color, FillFlag, LineThickness));
		return 0;
	}
}