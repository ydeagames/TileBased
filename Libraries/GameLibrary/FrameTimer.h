#pragma once

// <フレームタイマー>
class FrameTimer final
{
private:
	// 1秒 (=1,000,000μ秒)
	static const int ONE_SECOND = 1000000;

private:
	// フレームの経過時間[μs]
	float m_frame_delta_time;
	// フレームレート[fps]
	float m_frame_rate;
	// 前回の計測時間
	LONGLONG m_previous_time;
	// 現在の計測時間
	LONGLONG m_current_time;
	// フレームレート計測開始時間
	LONGLONG m_start_time;
	// フレーム数
	int m_frame_count;

public:
	FrameTimer();

	~FrameTimer();

	// リセット
	void Reset();
	// 更新
	void Update();

	float GetFrameDeltaTime(void);    // フレームの経過時間の取得
	float GetFrameRate(void);		  // フレームレートの取得
};
