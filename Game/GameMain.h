// @file   GameMain.h
//
// @brief  ゲーム関連のヘッダファイル
//
// @date   日付　2018/11/22
//
// @author 制作者名　YdeaGames

#pragma once
#include <vector>

// <システム>

	// <画面>
class Screen : public Singleton<Screen>
{
private:
	// ゲームタイトル
	std::string title;

	// 画面のサイズ[pixel]
	Vector2 size;

private:
	Screen();
	friend class Singleton<Screen>;

public:
	inline std::string GetTitle()
	{
		return title;
	}

	void SetTitle(const std::string& newtitle);

	inline Vector2 GetSize()
	{
		return size;
	}

	void SetSize(const Vector2& newsize);

	inline Bounds GetBounds()
	{
		return Bounds::CreateFromSize(Vector2::zero, size);
	}

	static inline Bounds Bounds()
	{
		return GetInstance().GetBounds();
	}
};

// <ゲーム>
class Game
{
private:
	FrameTimer* m_frame_timer;

public:
	Game();
	~Game();

	void Update(void);
	void Render(void);
};
