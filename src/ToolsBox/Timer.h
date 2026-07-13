#pragma once
#include "PrimitiveTypes.h"

class Timer
{
private:

	float64 m_start = 0.f;
	float64 m_end = 0.f;

public:

	Timer() = default;
	~Timer() = default;

	float64 Start();
	float64 End();

	float64 GetCurrentTime();

	void Sleep(int32 milliseconds);
	void ResetTimer();
};