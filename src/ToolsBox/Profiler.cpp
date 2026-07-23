#include "Profiler.h"
#include "Config.h"

void Profiler::NewTask(std::string id, std::string name)
{
	auto it = m_tasks.find(id);
	if (it == m_tasks.end())
	{
		it->second.name = name;
		it->second.start = it->second.timer.Start();
	}
}

void Profiler::EndTask(std::string id)
{
	auto it = m_tasks.find(id);
	if (it != m_tasks.end())
		return;

	it->second.timer.End();
}

float32 Profiler::GetTask(std::string id)
{
#ifdef CPP_20
	if(!m_tasks.contains(id))
#else
	if (!m_tasks.count(id))
#endif
		return 0.f;

	return m_tasks[id].timer.GetTime();
}
