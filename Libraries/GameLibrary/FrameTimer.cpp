#include "FrameTimer.h"

// <FrameTimer�N���X>
FrameTimer::FrameTimer()
	: m_frame_delta_time(0.0f)
	, m_frame_rate(0.0f)
	, m_previous_time(0)
	, m_current_time(0)
	, m_start_time(0)
	, m_frame_count(0)
{
}

// �f�X�g���N�^
FrameTimer::~FrameTimer()
{
}

// �t���[���^�C�}�[�̍X�V
void FrameTimer::Update()
{
	// ���Ԃ̌v��
	m_previous_time = m_current_time;
	m_current_time = GetNowHiPerformanceCount();


	// �t���[���̌o�ߎ��Ԃ̍X�V
	m_frame_delta_time = static_cast<float>(m_current_time - m_previous_time) / ONE_SECOND;


	// 1�b���Ƀt���[�����[�g�̍X�V
	m_frame_count++;
	if ((m_current_time - m_start_time) > ONE_SECOND)
	{
		m_frame_rate = static_cast<float>(m_frame_count * ONE_SECOND) / (m_current_time - m_start_time);
		m_start_time = m_current_time;
		m_frame_count = 0;
	}
}

// �t���[���^�C�}�[�̃��Z�b�g
void FrameTimer::Reset()
{
	m_previous_time = 0;
	m_current_time = 0;
	m_start_time = 0;
	m_frame_count = 0;
}

// �t���[���̌o�ߎ��Ԃ̎擾
float FrameTimer::GetFrameDeltaTime(void)
{
	return m_frame_delta_time;
}

// �t���[�����[�g�̎擾
float FrameTimer::GetFrameRate(void)
{
	return m_frame_rate;
}
