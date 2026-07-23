#pragma once
#include "PrimitiveTypes.h"


class Timer
{
private:

	float32 m_start = 0.f;
	float32 m_end	= 0.f;

public:

	Timer()  = default;
	~Timer() = default;

	float32 Start();
	float32 End();
	float32 GetTime();

	float32 GetCurrentTime();

	void Sleep(int32 milliseconds);
	void ResetTimer();
};