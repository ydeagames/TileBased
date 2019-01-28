#pragma once

// <�e�N�X�`��>
class Texture
{
public:
	std::vector<std::shared_ptr<TextureResource>> images;	// <�e�N�X�`��>
	float interval;
	bool loop_enable;

private:
	float firstTime;

public:
	// <�e�N�X�`���쐬>
	Texture();
	Texture(const std::shared_ptr<TextureResource>& image);
	Texture(const std::vector<std::shared_ptr<TextureResource>>& images, float interval, bool loop_enable = true);

public:
	// <�e�N�X�`���`��>
	const std::shared_ptr<TextureResource>& GetFrame() const;

	const std::shared_ptr<TextureResource>& GetFrame(float progress) const;

	// <�e�N�X�`���`��>
	void Render(const Quad& quad) const;
};
