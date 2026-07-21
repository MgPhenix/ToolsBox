#include "Profiler.h"
#include "Config.h"

void Profiler::NewTask(std::string id, std::string name)
{
	auto it = m_tasks.find(id);
	if (it == m_tasks.end())
	{
		it->second.name = name;
		it->second.timer.Start();
	}
}

void Profiler::EndTask(std::string id)
{
	auto it = m_tasks.find(id);
	if (it != m_tasks.end())
		return;

	it->second.timer.End();
}
