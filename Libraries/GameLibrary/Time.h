#pragma once
#include "Singleton.h"
#include "Timer.h"

class Time : public Singleton<Time>
{
public:
	Timer deltaTimer;
	static float deltaTime;
	Timer timer;
	static float time;

private:
	Time();
	friend class Singleton<Time>;

public:
	void InitializeTime();
	void UpdateTime();
};

