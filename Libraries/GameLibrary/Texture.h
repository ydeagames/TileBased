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
	Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& pivot = Vec2{ .5f, .5f });

	// <テクスチャ描画>
	void Render(const Vec2& center, const Vec2& scale, float angle) const;

	// <テクスチャ描画>
	void Render(const Transform& tranform) const;
};
