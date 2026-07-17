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

std::string GetName(const std::string& path)
{
	std::string name;
	bool canSave = false;
	for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--)
	{
		if (path[i] == '.')
		{
			canSave = true;
			continue;
		}

		if (path[i] == '/')
			canSave = false;

		if (canSave)
			name = path[i] + name;
	}

	return name;
}

std::string GetExtension(const std::string& path)
{
	std::string extension;
	for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--)
	{
		extension = path[i] + extension;
		if (path[i] == '.')
			return extension;
	}

	return extension;
}