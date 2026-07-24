/**
* @file Timer.h
* @brief Timer using std::chrono but will maybe use windows clock later
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "PrimitiveTypes.h"

/**
* @brief Timer who do timer thing like manage timer cause this is a timer
*/
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
	float32 GetEnd();

	float32 GetCurrentTime();

	void Sleep(int32 milliseconds);
	void ResetTimer();
};