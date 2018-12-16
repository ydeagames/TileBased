#include "Dependencies\pch.h"
#include "Time.h"

float Time::deltaTime = 0;
float Time::time = 0;

Time::Time()
	: deltaTimer(Timer{})
	, timer(Timer{})
{
}

void Time::InitializeTime()
{
	deltaTimer.Start(0);
	deltaTime = 0;
	timer.Start(0);
	time = 0;
}

void Time::UpdateTime()
{
	deltaTime = deltaTimer.GetTime();
	deltaTimer.Start(0);
	time = timer.GetTime();
}

