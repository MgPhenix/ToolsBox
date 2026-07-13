#include "Timer.h"
#include <chrono>
#include <thread>

float64 Timer::End()
{
    m_end = GetCurrentTime();
    return m_end;
}

float64 Timer::Start()
{
    m_start = GetCurrentTime();
    return m_start;
}

float64 Timer::GetCurrentTime()
{
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return static_cast<float64>(ms.count());
}

void Timer::Sleep(int32 milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Timer::ResetTimer()
{
    m_start = 0.f;
    m_end = 0.f;
}
