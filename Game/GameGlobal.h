#pragma once

class GameGlobal : public Singleton<GameGlobal>
{
public:
	std::shared_ptr<FontResource> titlefont;
	std::shared_ptr<FontResource> font;
	std::shared_ptr<TextureResource> movie;
	std::shared_ptr<TextureResource> icon;
	std::shared_ptr<TextureResource> background;
	std::shared_ptr<AudioResource> bgm01;
	std::shared_ptr<AudioResource> se01;
	std::shared_ptr<AudioResource> se02;
	std::shared_ptr<AudioResource> se03;

private:
	GameGlobal();
	friend class Singleton<GameGlobal>;

public:
	~GameGlobal();
};
