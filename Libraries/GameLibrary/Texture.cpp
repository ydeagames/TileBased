#include "Texture.h"

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture)
	: texture(texture)
{
}

// <テクスチャ描画>
void Texture::Render(const Quad& quad) const
{
	if (texture->IsValid())
		// スプライト描画
		DrawModiGraphF(
			quad.vertices[0].x, quad.vertices[0].y,
			quad.vertices[1].x, quad.vertices[1].y,
			quad.vertices[2].x, quad.vertices[2].y,
			quad.vertices[3].x, quad.vertices[3].y,
			texture->GetResource(),
			true
		);
}
