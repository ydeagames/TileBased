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
	TextureResource(const std::string& dir, const std::string& file);
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
	AudioResource(const std::string& dir, const std::string& file);
	AudioResource(const std::string& file);
	AudioResource(HSND id);
	virtual ~AudioResource();
};

class MovieResource : public Resource<HGRP>
{
public:
	static const std::string MOVIE_DIR;

public:
	MovieResource(const std::string& dir, const std::string& file);
	MovieResource(const std::string& file);
	MovieResource(HSND id);
	virtual ~MovieResource();
};

class FontFileResource : public Resource<std::string>
{
private:
	FontFileResource(const std::string& path);

public:
	virtual ~FontFileResource();

private:
	static std::unordered_map<std::string, std::weak_ptr<FontFileResource>> pool;

public:
	static std::shared_ptr<FontFileResource> Load(const std::string& path);
};

class FontResource : public Resource<HFNT>
{
public:
	static const std::string FONT_DIR;

private:
	std::shared_ptr<FontFileResource> fontfile;

public:
	FontResource(const std::string& dir, const std::string& file, const std::string& FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE);
	FontResource(const std::string& file, const std::string& FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE);
	FontResource(const std::string& FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE);
	FontResource(HFNT resource);
	virtual ~FontResource();
};

