#pragma once

class GameGlobal : public Singleton<GameGlobal>
{
public:
	std::shared_ptr<FontResource> titlefont;
	std::shared_ptr<FontResource> font;

private:
	GameGlobal();
	friend class Singleton<GameGlobal>;

public:
	~GameGlobal();
};
