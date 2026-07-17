#pragma once
#include <random>
#include <vector>
#include "PrimitiveTypes.h"



int32 GetRandomNumber(int32 min, int32 max);

/*Return the hash of a string using FNV_1A*/
uint64 HashFNV_1A(const std::string& str);

/*When you provide a path with an extension like "C:/folder/file.txt" it will return .txt
- If your path doesn't have extension it will just return the path*/
std::string GetExtension(const std::string& path);
// When you provide a path like "C:/folder/file.txt" it will return "file"
std::string GetName(const std::string& path);



template<typename T>
T Clamp(T val, T min, T max)
{
	if (val > max) return max;
	if (val < min) return min;
	return val;
}

//Return a random value from a vector
template<typename T>
T GetRandomValue(const std::vector<T>& vector)
{
	if (vector.empty()) return 0;

	return vector[GetRandomNumber(0, static_cast<int32>(vector.size()) - 1)];
}