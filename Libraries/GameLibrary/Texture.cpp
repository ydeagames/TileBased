#include "Texture.h"

// <�e�N�X�`���쐬>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <�e�N�X�`���쐬>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& pivot)
	: texture(texture)
	, pivot(pivot)
{
	anchor = {};
	size = {};

	if (texture->IsValid())
	{
		float width, height;
		if (GetGraphSizeF(texture->GetResource(), &width, &height) != -1)
			size = { width, height };
	}
}

// <�e�N�X�`���`��>
void Texture::Render(const Vec2& center, const Vec2& scale, float angle) const
{
	if (texture->IsValid())
		// �X�v���C�g�`��
		DrawRectRotaGraph3F(
			center.x, center.y,
			(int)anchor.x, (int)anchor.y,
			(int)size.x, (int)size.y,
			pivot.x * size.x, pivot.y * size.x,
			(double)scale.x, (double)scale.y,
			(double)angle,
			texture->GetResource(),
			TRUE
		);
}

// <�e�N�X�`���`��>
void Texture::Render(const Transform& tranform) const
{
	Render(tranform.position, tranform.scale, tranform.rotation);
}
