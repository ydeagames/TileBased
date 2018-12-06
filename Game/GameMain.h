// @file   GameMain.h
//
// @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//
// @date   ���t�@2018/11/22
//
// @author ����Җ��@YdeaGames

#pragma once
#include <vector>

// <�V�X�e��>

// �Q�[���^�C�g��
const char* const GAME_TITLE = "360���u���b�N����";

// <���>

// ��ʂ̃T�C�Y[pixel]
const Vec2 SCREEN_SIZE = { 640, 480 };

// ���
const Bounds SCREEN = { SCREEN_SIZE / 2, SCREEN_SIZE };

// <�Q�[��>
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
