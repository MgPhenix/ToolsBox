#pragma once
#include <random>
#include <vector>
#include "PrimitiveTypes.h"

template<typename T>
T Clamp(T val, T min, T max)
{
	if (val > max) return max;
	if (val < min) return min;
	return val;
}

int32 GetRandomNumber(int32 min, int32 max);

template<typename T>
T GetRandomValue(std::vector<T> vector)
{
	if (vector.empty()) return 0;

	return vector[GetRandomNumber(0, static_cast<int32>(vector.size()) - 1)];
}