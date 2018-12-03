#pragma once

// <�Q�[���^�C�}�[>>
class Timer final
{
private:
	// �~���b���b
	static const int RESOLUTION = 1000;

	// �J�n����
	int start_time;
	// �I������
	int last_time;
	// �ꎞ��~
	bool paused;
	// ��������
	float total;
public:
	// <�^�C�}�[�쐬>
	Timer();

	// <�^�C�}�[����>
	float GetTime();

	// <�^�C�}�[�ꎞ��~��>
	bool IsPaused();

	// <�^�C�}�[��~>
	Timer& Pause();

	// <�^�C�}�[���Z�b�g>
	Timer& Reset();

	// <�^�C�}�[�ĊJ>
	Timer& Resume();

	// <�^�C�}�[�Z�b�g>
	Timer& Set(float new_time);

	// <�^�C�}�[�c�莞�ԃZ�b�g>
	Timer& SetRemaining(float remaining);

	// <�^�C�}�[�c�莞�ԃ��Z�b�g>
	Timer& ResetRemaining();

	// <�g�[�^�����ԃZ�b�g>
	Timer& SetTotal(float total);

	// <�g�[�^�����ԃZ�b�g&�c�莞�ԃ��Z�b�g&�ĊJ>
	Timer& Start(float total);

	// <�g�[�^�����Ԏ擾>
	float GetTotal();

	// <�i���擾>
	float GetProgress();

	// <�^�C�}�[�c�莞��>
	float GetRemaining();

	// <�^�C�}�[�o�ߎ���>
	float GetElapsed();

	// <�^�C�}�[�I������>
	bool IsFinished();
};