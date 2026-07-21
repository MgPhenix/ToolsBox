#pragma once
#include <string>
#include <vector>
#include "PrimitiveTypes.h"

enum class Severity
{
	DEBUG,
	INFO,
	WARN,
	ERROR,
	CRITICAL
};


std::string SevertityToString(Severity severity);

/*Return the hash of a string using FNV_1A*/
uint64 HashFNV_1A(const std::string& str);

/*When you provide a path with an extension like "C:/folder/file.txt" it will return .txt
- If your path doesn't have an extension it will just return the path*/
std::string GetPathExtension(const std::string& path);
// When you provide a path like "C:/folder/file.txt" it will return "file"
std::string GetPathName(const std::string& path);

//Return time in the format hours:minutes:seconds
std::string GetLocalTime();


template<typename T>
T Clamp(T val, T min, T max);


int32 GetRandomNumber(int32 min, int32 max);

//Return a random value from a vector
template<typename T>
T GetRandomValue(const std::vector<T>& vector);

#include "Utils.inl"