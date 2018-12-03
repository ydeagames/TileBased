#include "FrameTimer.h"

// <FrameTimerクラス>
FrameTimer::FrameTimer()
	: m_frame_delta_time(0.0f)
	, m_frame_rate(0.0f)
	, m_previous_time(0)
	, m_current_time(0)
	, m_start_time(0)
	, m_frame_count(0)
{
}

// デストラクタ
FrameTimer::~FrameTimer()
{
}

// フレームタイマーの更新
void FrameTimer::Update()
{
	// 時間の計測
	m_previous_time = m_current_time;
	m_current_time = GetNowHiPerformanceCount();


	// フレームの経過時間の更新
	m_frame_delta_time = static_cast<float>(m_current_time - m_previous_time) / ONE_SECOND;


	// 1秒毎にフレームレートの更新
	m_frame_count++;
	if ((m_current_time - m_start_time) > ONE_SECOND)
	{
		m_frame_rate = static_cast<float>(m_frame_count * ONE_SECOND) / (m_current_time - m_start_time);
		m_start_time = m_current_time;
		m_frame_count = 0;
	}
}

// フレームタイマーのリセット
void FrameTimer::Reset()
{
	m_previous_time = 0;
	m_current_time = 0;
	m_start_time = 0;
	m_frame_count = 0;
}

// フレームの経過時間の取得
float FrameTimer::GetFrameDeltaTime(void)
{
	return m_frame_delta_time;
}

// フレームレートの取得
float FrameTimer::GetFrameRate(void)
{
	return m_frame_rate;
}
