#include "Texture.h"

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <テクスチャ作成>
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

// <テクスチャ描画>
void Texture::Render(const Vec2& center, const Vec2& scale, float angle) const
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
void Texture::Render(const Transform& tranform) const
{
	Render(tranform.position, tranform.scale, tranform.rotation);
}
