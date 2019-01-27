#include "Graphics.h"
#define DX(exp) if (exp) { return -1; }

namespace Graphics
{
	// <ベクトルを描画>
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

	// 回転直方体
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

	// 四角形画像
	int DrawQuadGraph(const Quad& quad, const std::shared_ptr<TextureResource>& texture)
	{
		DX(DrawModiGraphF(
			quad.vertices[0].x, quad.vertices[0].y,
			quad.vertices[1].x, quad.vertices[1].y,
			quad.vertices[2].x, quad.vertices[2].y,
			quad.vertices[3].x, quad.vertices[3].y,
			texture->GetResource(),
			true
		));
		return 0;
	}

	// 四角形
	int DrawQuad(const Quad & quad, unsigned int Color, int FillFlag, float LineThickness)
	{
		DX(DrawQuadrangleAA(
			quad.vertices[0].x, quad.vertices[0].y,
			quad.vertices[1].x, quad.vertices[1].y,
			quad.vertices[2].x, quad.vertices[2].y,
			quad.vertices[3].x, quad.vertices[3].y,
			Color, FillFlag, LineThickness
		));
		return 0;
	}

	// 四角形フォント
	int DrawQuadString(const Quad& quad, unsigned int Color, const std::shared_ptr<FontResource>& font, String str)
	{
		if (DrawStringFToHandle(quad.vertices[0].x, quad.vertices[0].y, str.operator LPCSTR(), Color, font->GetResource(), 0U, false))
			return -1;
		//if (DrawModiStringFToHandle(
		//	quad.vertices[0].x, quad.vertices[0].y,
		//	quad.vertices[1].x, quad.vertices[1].y,
		//	quad.vertices[2].x, quad.vertices[2].y,
		//	quad.vertices[3].x, quad.vertices[3].y,
		//	Color, font->GetResource(), 0U, false, str.operator LPCSTR()
		//))
			return -1;
		return 0;
	}
}