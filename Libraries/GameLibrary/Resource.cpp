#include "Resource.h"

const std::string TextureResource::TEXTURE_DIR = "Resources/Textures/";
const std::string AudioResource::AUDIO_DIR = "Resources/Audio/";
const std::string MovieResource::MOVIE_DIR = "Resources/Movies/";
const std::string FontResource::FONT_DIR = "Resources/Fonts/";

std::unordered_map<std::string, std::weak_ptr<FontFileResource>> FontFileResource::pool;

TextureResource::TextureResource(const std::string & dir, const std::string & file)
	: Resource(-1)
	, source(nullptr)
{
	resource = LoadGraph((dir + file).c_str());
}

TextureResource::TextureResource(const std::string& file)
	: TextureResource(TEXTURE_DIR, file)
{
}

TextureResource::TextureResource(HGRP id)
	: Resource(-1)
	, source(nullptr)
{
	resource = id;
}

TextureResource::TextureResource(const std::shared_ptr<TextureResource>& source, const Bounds& bounds)
	: Resource(-1)
	, source(source)
{
	resource = DerivationGraphF(bounds.GetMin().x, bounds.GetMin().y, bounds.GetSize().x, bounds.GetSize().y, source->GetResource());
}

TextureResource::~TextureResource()
{
	DeleteGraph(resource);
}

std::shared_ptr<TextureResource> TextureResource::CreateMissingTexture()
{
	HGRP tex = MakeScreen(16, 16);
	screen_start(tex)
	{
		DrawBox(0, 0, 15, 15, Colors::Black, true);
		DrawBox(0, 0, 7, 7, Colors::Fuchsia, true);
		DrawBox(8, 8, 15, 15, Colors::Fuchsia, true);
	} screen_end;
	return std::make_shared<TextureResource>(tex);
}

std::shared_ptr<TextureResource> TextureResource::GetMissingTexture()
{
	static auto nulltexture = CreateMissingTexture();
	return nulltexture;
}

AudioResource::AudioResource(const std::string & dir, const std::string & file)
	: Resource(-1)
{
	resource = LoadSoundMem((dir + file).c_str());
}

AudioResource::AudioResource(const std::string& file)
	: AudioResource(AUDIO_DIR, file)
{
}

AudioResource::AudioResource(HSND id)
	: Resource(-1)
{
	resource = id;
}

AudioResource::~AudioResource()
{
	DeleteSoundMem(resource);
}

MovieResource::MovieResource(const std::string & dir, const std::string & file)
	: Resource(-1)
{
	resource = LoadGraph((MOVIE_DIR + file).c_str());
}

MovieResource::MovieResource(const std::string& file)
	: MovieResource(MOVIE_DIR, file)
{
}

MovieResource::MovieResource(HSND id)
	: Resource(-1)
{
	resource = id;
}

MovieResource::~MovieResource()
{
	DeleteGraph(resource);
}

FontFileResource::FontFileResource(const std::string& path)
	: Resource("")
{
	if (AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL) > 0)
		resource = path;
}

FontFileResource::~FontFileResource()
{
	RemoveFontResourceEx(resource.c_str(), FR_PRIVATE, NULL);
}

std::shared_ptr<FontFileResource> FontFileResource::Load(const std::string& path)
{
	if (auto res = pool[path].lock())
		return res;
	struct Obj : FontFileResource {
		Obj(const std::string& path) : FontFileResource(path) {}
	};
	auto res = std::make_shared<Obj>(path);
	pool[path] = res;
	return res;
}

FontResource::FontResource(const std::string & dir, const std::string & file, const std::string & FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic)
	: Resource(-1)
	, fontfile(nullptr)
{
	fontfile = FontFileResource::Load(dir + file);
	if (fontfile->IsValid())
		resource = CreateFontToHandle(FontName.c_str(), Size, Thick, FontType, CharSet, EdgeSize, Italic);
}

FontResource::FontResource(const std::string & file, const std::string & FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic)
	: FontResource(FONT_DIR, file, FontName, Size, Thick, FontType, CharSet, EdgeSize, Italic)
{
}

FontResource::FontResource(const std::string & FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic)
	: FontResource(-1)
{
	resource = CreateFontToHandle(FontName.c_str(), Size, Thick, FontType, CharSet, EdgeSize, Italic);
}

FontResource::FontResource(HFNT id)
	: Resource(-1)
{
	resource = id;
}

FontResource::~FontResource()
{
	DeleteFontToHandle(resource);
}
