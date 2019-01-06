#pragma once

namespace Graphics
{
	// <ƒxƒNƒgƒ‹‚ð•`‰æ>
	int DrawVector(const Vector2& vector, const Vector2& base, Color color, float Thickness = 1.f);

	// ‰ñ“]’¼•û‘Ì
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);

	// ŽlŠpŒ`‰æ‘œ
	int DrawQuadGraph(const Quad& quad, const std::shared_ptr<TextureResource>& texture);

	// ŽlŠpŒ`
	int DrawQuad(const Quad& quad, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
}