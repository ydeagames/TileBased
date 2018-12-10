#pragma once
#include "Resource.h"

// <テクスチャ>
class Texture final
{
public:
	std::shared_ptr<TextureResource> texture;				// <テクスチャ>
	Vec2 anchor;				// <テクスチャ基点>
	Vec2 size;					// <テクスチャサイズ>

public:
	// <テクスチャ作成>
	Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size);

	// <テクスチャ作成>
	Texture(const std::shared_ptr<TextureResource>& texture);

	// <テクスチャ描画>
	void Render(const Vec2& center, const Vec2& scale, float angle, const Vec2& pivot) const;

	// <テクスチャ描画>
	void Render(const Transform& tranform, const Vec2& pivot) const;
};
