#include "Timer.h"
#include <chrono>
#include <thread>

float32 Timer::End()
{
    m_end = GetCurrentTime();
    return m_end;
}

float32 Timer::GetTime()
{
    return GetCurrentTime() - m_start;
}

float32 Timer::GetEnd()
{
    return m_end;
}

float32 Timer::Start()
{
    m_start = GetCurrentTime();
    return m_start;
}

float32 Timer::GetCurrentTime()
{
    auto now = std::chrono::steady_clock::now();
    auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return static_cast<float32>(ms.count());
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

//double PCFreq = 0.0;
//int64 CounterStart = 0;
//
//void StartCounter()
//{
//    LARGE_INTEGER li;
//    if (!QueryPerformanceFrequency(&li))
//        std::cout << "QueryPerformanceFrequency failed!" << std::endl;
//
//    PCFreq = double(li.QuadPart) / 1000.0;
//
//    QueryPerformanceCounter(&li);
//    CounterStart = li.QuadPart;
//}
//double GetCounter()
//{
//    LARGE_INTEGER li;
//    QueryPerformanceCounter(&li);
//    return double(li.QuadPart - CounterStart) / PCFreq;
//}