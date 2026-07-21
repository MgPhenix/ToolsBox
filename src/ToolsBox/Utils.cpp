#include "Utils.h"
#include <random>


std::string SevertityToString(Severity severity)
{
	switch (severity)
	{
	case Severity::DEBUG:	 return "DEBUG";
	case Severity::INFO:	 return "INFO";
	case Severity::WARN:	 return "WARN";
	case Severity::ERROR:	 return "ERROR";
	case Severity::CRITICAL: return "CRTICAL";
	default:
		return "";
	}
}
int32 GetRandomNumber(int32 min, int32 max)
{
	static std::random_device rd;

	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

uint64 HashFNV_1A(const std::string& str)
{
	uint64 hash = 14695981039346656037ULL;
	for (byte c : str)
	{
		hash ^= c;
		hash *= 1099511628211ULL;
	}
	return hash;
}

std::string GetPathName(const std::string& path)
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

std::string GetLocalTime()
{
	time_t timestamp = time(NULL);
	struct tm datetime;
	localtime_s(&datetime, &timestamp);
	char output[50];

	strftime(output, 50, "%H:%M:%S", &datetime);
	return std::string(output);
}

std::string GetPathExtension(const std::string& path)
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