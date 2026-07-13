#include "Utils.h"

int32 GetRandomNumber(int32 min, int32 max)
{
	static std::random_device rd;

	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}
