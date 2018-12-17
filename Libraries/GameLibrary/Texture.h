#pragma once

// <�e�N�X�`��>
class Texture final
{
public:
	std::shared_ptr<TextureResource> texture;				// <�e�N�X�`��>

public:
	// <�e�N�X�`���쐬>
	Texture(const std::shared_ptr<TextureResource>& texture);

	// <�e�N�X�`���`��>
	void Render(const Quad& quad) const;
};
