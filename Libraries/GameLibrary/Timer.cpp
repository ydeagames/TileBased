#include "Timer.h"

// <�����X�V>
Timer::TimePoint Timer::tick = -1;

// <�^�C�}�[�쐬>
Timer::Timer(void) :
	start_time(-1),
	last_time(-1),
	paused(true),
	total(0)
{
	// �^�C�}�[�����Z�b�g
	Reset();
}

// <�����X�V>
void Timer::Tick()
{
	tick = GetNowHiPerformanceCount();
}

// <�����擾>
Timer::TimePoint Timer::GetNow()
{
	if (tick < 0)
		return GetNowHiPerformanceCount();
	return tick;
}

// <�^�C�}�[����>
float Timer::GetTime()
{
	// �ꎞ��~����ĂȂ���΍X�V����
	if (!paused)
		last_time = GetNow() - start_time;
	return static_cast<float>(last_time) / RESOLUTION;
}

// <�^�C�}�[�ꎞ��~��>
bool Timer::IsPaused()
{
	return paused;
}

// <�^�C�}�[��~>
Timer& Timer::Pause()
{
	// �ꎞ��~����ĂȂ���΍X�V����
	if (!paused)
		last_time = GetNow() - start_time;
	paused = true;
	return *this;
}

// <�^�C�}�[���Z�b�g>
Timer& Timer::Reset()
{
	Set(0);
	return *this;
}

// <�^�C�}�[�ĊJ>
Timer& Timer::Resume()
{
	// �ꎞ��~����Ă���΍ĊJ�J�n�������v�Z���čX�V
	if (paused)
		start_time = GetNow() - last_time;
	paused = false;
	return *this;
}

// <�^�C�}�[�Z�b�g>
Timer& Timer::Set(float new_time)
{
	// �~���b
	TimePoint new_time_in_ticks = static_cast<TimePoint>(new_time * RESOLUTION);
	// �J�n�������v�Z
	start_time = GetNow() - new_time_in_ticks;
	// �I���������v�Z
	last_time = new_time_in_ticks;
	return *this;
}

// <�^�C�}�[�c�莞�ԃZ�b�g>
Timer& Timer::SetRemaining(float remaining)
{
	Set(-remaining);
	return *this;
}

// <�^�C�}�[�c�莞��>
float Timer::GetRemaining()
{
	return -Timer::GetTime();
}

// <�^�C�}�[�c�莞�ԃ��Z�b�g>
Timer& Timer::ResetRemaining()
{
	SetRemaining(GetTotal());
	return *this;
}

// <�g�[�^�����ԃZ�b�g>
Timer& Timer::SetTotal(float new_total)
{
	total = new_total;
	return *this;
}

// <�g�[�^�����ԃZ�b�g&�c�莞�ԃ��Z�b�g&�ĊJ>
Timer& Timer::Start(float new_total)
{
	return SetTotal(new_total).ResetRemaining().Resume();
}

// <�g�[�^�����Ԏ擾>
float Timer::GetTotal()
{
	return total;
}

// <�i���擾>
float Timer::GetProgress()
{
	return GetElapsed() / GetTotal();
}

// <�^�C�}�[�o�ߎ���>
float Timer::GetElapsed()
{
	return GetTotal() - GetRemaining();
}

// <�^�C�}�[�I������>
bool Timer::IsFinished()
{
	return GetTime() >= 0;
}
