#include "Timer.h"

// <タイマー作成>
Timer::Timer(void) :
	start_time(-1),
	last_time(-1),
	paused(true),
	total(0)
{
	// タイマーをリセット
	Reset();
}

// <タイマー時間>
float Timer::GetTime()
{
	// 一時停止されてなければ更新する
	if (!paused)
		last_time = GetNowCount() - start_time;
	return static_cast<float>(last_time) / RESOLUTION;
}

// <タイマー一時停止中>
bool Timer::IsPaused()
{
	return paused;
}

// <タイマー停止>
Timer& Timer::Pause()
{
	// 一時停止されてなければ更新する
	if (!paused)
		last_time = GetNowCount() - start_time;
	paused = TRUE;
	return *this;
}

// <タイマーリセット>
Timer& Timer::Reset()
{
	Set(0);
	return *this;
}

// <タイマー再開>
Timer& Timer::Resume()
{
	// 一時停止されていれば再開開始時刻を計算して更新
	if (paused)
		start_time = GetNowCount() - last_time;
	paused = FALSE;
	return *this;
}

// <タイマーセット>
Timer& Timer::Set(float new_time)
{
	// ミリ秒
	int new_time_in_ticks = static_cast<int>(new_time * RESOLUTION);
	// 開始時刻を計算
	start_time = GetNowCount() - new_time_in_ticks;
	// 終了時刻を計算
	last_time = new_time_in_ticks;
	return *this;
}

// <タイマー残り時間セット>
Timer& Timer::SetRemaining(float remaining)
{
	Set(-remaining);
	return *this;
}

// <タイマー残り時間>
float Timer::GetRemaining()
{
	return -Timer::GetTime();
}

// <タイマー残り時間リセット>
Timer& Timer::ResetRemaining()
{
	SetRemaining(GetTotal());
	return *this;
}

// <トータル時間セット>
Timer& Timer::SetTotal(float new_total)
{
	total = new_total;
	return *this;
}

// <トータル時間セット&残り時間リセット&再開>
Timer& Timer::Start(float new_total)
{
	return SetTotal(new_total).ResetRemaining().Resume();
}

// <トータル時間取得>
float Timer::GetTotal()
{
	return total;
}

// <進捗取得>
float Timer::GetProgress()
{
	return GetElapsed() / GetTotal();
}

// <タイマー経過時間>
float Timer::GetElapsed()
{
	return GetTotal() - GetRemaining();
}

// <タイマー終了判定>
bool Timer::IsFinished()
{
	return GetTime() >= 0;
}
