#include "Resource.h"

const std::string TextureResource::TEXTURE_DIR = "Resources/Textures/";
const std::string AudioResource::AUDIO_DIR = "Resources/Audio/";
const std::string MovieResource::MOVIE_DIR = "Resources/Movies/";
const std::string FontFileResource::FONT_DIR = "Resources/Fonts/";

TextureResource::TextureResource(const std::string& file)
	: Resource(-1)
{
	resource = LoadGraph((TEXTURE_DIR + file).c_str());
}

TextureResource::~TextureResource()
{
	DeleteGraph(resource);
}

TextureResource::TextureResource(HGRP id)
	: Resource(-1)
{
	resource = id;
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

AudioResource::AudioResource(const std::string& file)
	: Resource(-1)
{
	resource = LoadSoundMem((AUDIO_DIR + file).c_str());
}

AudioResource::~AudioResource()
{
	DeleteSoundMem(resource);
}

MovieResource::MovieResource(const std::string& file)
	: Resource(-1)
{
	resource = LoadGraph((MOVIE_DIR + file).c_str());
}

MovieResource::~MovieResource()
{
	DeleteGraph(resource);
}

FontResource::FontResource(HFNT resource)
	: Resource(resource)
{
}

FontResource::FontResource(const std::string & FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic)
	: FontResource(-1)
{
	resource = CreateFontToHandle(FontName.c_str(), Size, Thick, FontType, CharSet, EdgeSize, Italic);
}

FontResource::~FontResource()
{
	DeleteFontToHandle(resource);
}

FontFileResource::FontFileResource(const std::string & file, const std::string & FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic)
	: FontResource(-1)
	, file(file)
{
	if (AddFontResourceEx((FONT_DIR + file).c_str(), FR_PRIVATE, NULL) > 0)
		resource = CreateFontToHandle(FontName.c_str(), Size, Thick, FontType, CharSet, EdgeSize, Italic);
}

FontFileResource::~FontFileResource()
{
	RemoveFontResourceEx((FONT_DIR + file).c_str(), FR_PRIVATE, NULL);
}
