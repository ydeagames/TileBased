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

// ゲームタイトル
const char* const GAME_TITLE = "360°ブロック崩し";

// <画面>

// 画面のサイズ[pixel]
const Vec2 SCREEN_SIZE = { 640, 480 };

// 画面
const Bounds SCREEN = { SCREEN_SIZE / 2, SCREEN_SIZE };

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
