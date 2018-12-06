#pragma once
#include "Resource.h"

// <�e�N�X�`��>
class Texture final
{
public:
	std::shared_ptr<TextureResource> texture;				// <�e�N�X�`��>
	Vec2 anchor;				// <�e�N�X�`����_>
	Vec2 size;					// <�e�N�X�`���T�C�Y>
	Vec2 pivot;					// <�e�N�X�`�����S>

public:
	// <�e�N�X�`���쐬>
	Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot = Vec2{ .5f, .5f });

	// <�e�N�X�`���쐬>
	Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& pivot = Vec2{ .5f, .5f });

	// <�e�N�X�`���`��>
	void Render(const Vec2& center, const Vec2& scale, float angle) const;

	// <�e�N�X�`���`��>
	void Render(const Transform& tranform) const;
};
