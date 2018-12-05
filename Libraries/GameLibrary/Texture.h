#pragma once
#include "Resource.h"

// <テクスチャ>
class Texture final
{
public:
	std::shared_ptr<TextureResource> texture;				// <テクスチャ>
	Vec2 anchor;				// <テクスチャ基点>
	Vec2 size;					// <テクスチャサイズ>
	Vec2 pivot;					// <テクスチャ中心>

public:
	// <テクスチャ作成>
	Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot = Vec2{ .5f, .5f });

	// <テクスチャ作成>
	Texture(const std::shared_ptr<TextureResource>& texture);

	// <テクスチャなし>
	Texture();
};

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <テクスチャ作成>
Texture::Texture(const std::shared_ptr<TextureResource>& texture) :
	texture(texture)
{
	anchor = {};
	size = {};
	pivot = { .5f, .5f };

	if (texture->IsValid())
	{
		float width, height;
		if (GetGraphSizeF(texture->GetResource(), &width, &height) != -1)
			size = { width, height };
	}
}