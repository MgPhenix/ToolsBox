#include "Utils.h"

template<typename T>
T Clamp(T val, T min, T max)
{
	if (val > max) return max;
	if (val < min) return min;
	return val;
}


template<typename T>
T GetRandomValue(const std::vector<T>& vector)
{
	if (vector.empty()) return 0;

	return vector[GetRandomNumber(0, static_cast<int32>(vector.size()) - 1)];
}