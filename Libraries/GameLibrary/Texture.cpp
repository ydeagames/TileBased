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
		Graphics::DrawQuadGraph(quad, texture);
}
