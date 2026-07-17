#include "Utils.h"

int32 GetRandomNumber(int32 min, int32 max)
{
	static std::random_device rd;

	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

uint64 HashFNV_1A(const std::string& str)
{
	//FNV 1a because why not
	uint64 hash = 14695981039346656037ULL;
	for (byte c : str)
	{
		hash ^= c;
		hash *= 1099511628211ULL;
	}
	return hash;
}
