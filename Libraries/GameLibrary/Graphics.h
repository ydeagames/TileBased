#pragma once
#include "String.h"

namespace Graphics
{
	// <�x�N�g����`��>
	int DrawVector(const Vector2& vector, const Vector2& base, Color color, float Thickness = 1.f);

	// ��]������
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);

	// �l�p�`�摜
	int DrawQuadGraph(const Quad& quad, const std::shared_ptr<TextureResource>& texture);

	// �l�p�`
	int DrawQuad(const Quad& quad, unsigned int Color, int FillFlag, float LineThickness = 1.0f);

	// �l�p�`�t�H���g
	int DrawQuadString(const Quad & quad, unsigned int Color, const std::shared_ptr<FontResource>& font, String str);
}