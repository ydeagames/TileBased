#pragma once

// <テクスチャ>
class Texture final
{
public:
	std::shared_ptr<TextureResource> texture;				// <テクスチャ>

public:
	// <テクスチャ作成>
	Texture(const std::shared_ptr<TextureResource>& texture);

	// <テクスチャ描画>
	void Render(const Quad& quad) const;
};
