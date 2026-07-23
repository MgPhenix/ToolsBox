#pragma once
#include "Timer.h"
#include <unordered_map>
#include <string>


struct Task
{
	Timer		timer;
	std::string name;
	float32		start;
};


class Profiler
{
private:

	static std::unordered_map<std::string, Task> m_tasks;

public:

	static void NewTask(std::string id, std::string name = "");
	static void EndTask(std::string id);
	static float32 GetTask(std::string id);
};