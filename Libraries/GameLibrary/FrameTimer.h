#pragma once

// <�t���[���^�C�}�[>
class FrameTimer final
{
private:
	// 1�b (=1,000,000�ʕb)
	static const int ONE_SECOND = 1000000;

private:
	// �t���[���̌o�ߎ���[��s]
	float m_frame_delta_time;
	// �t���[�����[�g[fps]
	float m_frame_rate;
	// �O��̌v������
	LONGLONG m_previous_time;
	// ���݂̌v������
	LONGLONG m_current_time;
	// �t���[�����[�g�v���J�n����
	LONGLONG m_start_time;
	// �t���[����
	int m_frame_count;

public:
	FrameTimer();

	~FrameTimer();

	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();

	float GetFrameDeltaTime(void);    // �t���[���̌o�ߎ��Ԃ̎擾
	float GetFrameRate(void);		  // �t���[�����[�g�̎擾
};
