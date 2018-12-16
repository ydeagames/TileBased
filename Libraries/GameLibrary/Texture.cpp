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
		DrawModiGraphF(
			quad.vertices[0].x, quad.vertices[0].y,
			quad.vertices[1].x, quad.vertices[1].y,
			quad.vertices[2].x, quad.vertices[2].y,
			quad.vertices[3].x, quad.vertices[3].y,
			texture->GetResource(),
			true
		);
}
