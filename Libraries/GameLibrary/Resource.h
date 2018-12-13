#pragma once

template <class T>
class Resource
{
protected:
	T resource;
	T default_resource;

public:
	Resource(const T& default_resource)
		: resource(default_resource)
		, default_resource(default_resource) {};
	virtual ~Resource() = default;
	Resource(const Resource &) = delete;
	Resource& operator=(const Resource &) = delete;

public:
	const T& GetResource() const
	{
		return resource;
	}

	bool IsValid() const
	{
		return resource != default_resource;
	}
};

class TextureResource : public Resource<HGRP>
{
public:
	static const std::string TEXTURE_DIR;

private:
	std::shared_ptr<TextureResource> source;

public:
	TextureResource(const std::string& file);
	TextureResource(HGRP id);
	TextureResource(const std::shared_ptr<TextureResource>& source, const Bounds& bounds);
	virtual ~TextureResource();

private:
	static std::shared_ptr<TextureResource> CreateMissingTexture();

public:
	static std::shared_ptr<TextureResource> GetMissingTexture();
};

class AudioResource : public Resource<HSND>
{
public:
	static const std::string AUDIO_DIR;

public:
	AudioResource(const std::string& file);
	virtual ~AudioResource();
};

class MovieResource : public Resource<HGRP>
{
public:
	static const std::string MOVIE_DIR;

public:
	MovieResource(const std::string& file);
	virtual ~MovieResource();
};

class FontResource : public Resource<HFNT>
{
protected:
	FontResource(HFNT resource);

public:
	FontResource(const std::string& FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE);
	virtual ~FontResource();
};

class FontFileResource : public FontResource
{
public:
	static const std::string FONT_DIR;

protected:
	std::string file;

public:
	FontFileResource(const std::string& file, const std::string& FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE);
	virtual ~FontFileResource();
};

