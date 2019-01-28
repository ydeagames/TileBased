#pragma once

// <テクスチャ>
class Texture
{
public:
	std::vector<std::shared_ptr<TextureResource>> images;	// <テクスチャ>
	float interval;
	bool loop_enable;

private:
	float firstTime;

public:
	// <テクスチャ作成>
	Texture();
	Texture(const std::shared_ptr<TextureResource>& image);
	Texture(const std::vector<std::shared_ptr<TextureResource>>& images, float interval, bool loop_enable = true);

public:
	// <テクスチャ描画>
	const std::shared_ptr<TextureResource>& GetFrame() const;

	const std::shared_ptr<TextureResource>& GetFrame(float progress) const;

	// <テクスチャ描画>
	void Render(const Quad& quad) const;
};
