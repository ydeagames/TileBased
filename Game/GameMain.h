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

	// <���>
class Screen : public Singleton<Screen>
{
private:
	// �Q�[���^�C�g��
	std::string title;

	// ��ʂ̃T�C�Y[pixel]
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
