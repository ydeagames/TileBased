#include "Texture.h"

// <テクスチャ作成>
Texture::Texture()
	: Texture(std::shared_ptr<TextureResource>{})
{
}

Texture::Texture(const std::shared_ptr<TextureResource>& image)
	: Texture(std::vector<std::shared_ptr<TextureResource>>{ image }, 1)
{
}

Texture::Texture(const std::vector<std::shared_ptr<TextureResource>>& images, float interval, bool loop_enable)
	: images(images)
	, interval(interval)
	, loop_enable(loop_enable)
	, firstTime(Time::time)
{
}

const std::shared_ptr<TextureResource>& Texture::GetFrame() const
{
	float time = Time::time - firstTime;
	int totalframe = static_cast<int>(time / interval);
	int size = static_cast<int>(images.size());
	int frame = loop_enable ? MathUtils::Loop(totalframe, size) : std::min(totalframe, size - 1);
	return images[frame];
}

const std::shared_ptr<TextureResource>& Texture::GetFrame(float progress) const
{
	int size = static_cast<int>(images.size());
	int totalframe = static_cast<int>(progress * size);
	int frame = loop_enable ? MathUtils::Loop(totalframe, size) : std::min(totalframe, size - 1);
	return images[frame];
}

// <テクスチャ描画>
void Texture::Render(const Quad& quad) const
{
	const auto& texture = GetFrame();
	if (texture->IsValid())
		// スプライト描画
		Graphics::DrawQuadGraph(quad, texture);
}
