#include "Texture.h"

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size)
	: texture(texture)
	, anchor(anchor)
	, size(size)
{
}

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture)
	: texture(texture)
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

// <テクスチャ描画>
void Texture::Render(const Vec2& center, const Vec2& scale, float angle, const Vec2& pivot) const
{
	if (texture->IsValid())
		// スプライト描画
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

// <テクスチャ描画>
void Texture::Render(const Transform& tranform, const Vec2& pivot) const
{
	Render(tranform.position, tranform.scale, tranform.rotation, pivot);
}
