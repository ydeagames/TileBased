#pragma once
#include "String.h"

namespace Graphics
{
	// <ベクトルを描画>
	int DrawVector(const Vector2& vector, const Vector2& base, Color color, float Thickness = 1.f);

	// 回転直方体
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);

	// 四角形画像
	int DrawQuadGraph(const Quad& quad, const std::shared_ptr<TextureResource>& texture);

	// 四角形
	int DrawQuad(const Quad& quad, unsigned int Color, int FillFlag, float LineThickness = 1.0f);

	// 四角形フォント
	int DrawQuadString(const Quad & quad, unsigned int Color, const std::shared_ptr<FontResource>& font, String str);
}