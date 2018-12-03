#pragma once

class GameGlobal : public Singleton<GameGlobal>
{
public:
	std::shared_ptr<FontFileResource> titlefont;
	std::shared_ptr<FontFileResource> font;

private:
	GameGlobal();
	friend class Singleton<GameGlobal>;

public:
	~GameGlobal();
};

