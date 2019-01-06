#include "Texture.h"

// <�e�N�X�`���쐬>
Texture::Texture(const std::shared_ptr<TextureResource>& texture)
	: texture(texture)
{
}

// <�e�N�X�`���`��>
void Texture::Render(const Quad& quad) const
{
	if (texture->IsValid())
		// �X�v���C�g�`��
		Graphics::DrawQuadGraph(quad, texture);
}
