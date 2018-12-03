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

public:
	const T& GetResource()
	{
		return resource;
	}

	const T& IsValid()
	{
		return resource != default_resource;
	}
};

class TextureResource : public Resource<HGRP>
{
public:
	static const std::string TEXTURE_DIR;

public:
	TextureResource(const std::string& file);
	virtual ~TextureResource();
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

