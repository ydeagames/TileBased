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
