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
	Texture(const std::shared_ptr<TextureResource>& texture);

	// <�e�N�X�`���Ȃ�>
	Texture();
};

// <�e�N�X�`���쐬>
Texture::Texture(const std::shared_ptr<TextureResource>& texture, const Vec2& anchor, const Vec2& size, const Vec2& pivot) :
	texture(texture),
	anchor(anchor),
	size(size),
	pivot(pivot)
{
}

// <�e�N�X�`���쐬>
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