// @file   GameMain.h
//
// @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//
// @date   ���t�@2018/11/22
//
// @author ����Җ��@YdeaGames

#pragma once

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
