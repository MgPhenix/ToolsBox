#include "ThreadPool.h"
#include "PrimitiveTypes.h"
#include "SharedPtr.h"

ThreadPool::ThreadPool(size_t ThreadNbr) : 
	m_stop(false)
{
	for (size_t i = 0; i < ThreadNbr; i++)
	{
		m_threads.emplace_back([this]()
		{
			WorkerLoop();
		});
	}
}

ThreadPool::ThreadPool() :
	m_stop(false)
{
	uint32 threadNbr = std::thread::hardware_concurrency() - 1;
	for (uint32 i = 0; i < threadNbr; i++)
	{
		m_threads.emplace_back([this]()
			{
				WorkerLoop();
			});
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_stop = true;
	}

	m_condition.notify_all();

	for (std::thread& thread : m_threads)
		thread.join();
}

void ThreadPool::WorkerLoop()
{
	while (true)
	{
		std::function<void()> task;
		
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			
			m_condition.wait(lock, [this] { 
				return m_stop || !m_tasks.empty(); 
			});

			if (m_stop && m_tasks.empty())
				return;

			task = std::move(m_tasks.front());
			m_tasks.pop();
		}

		task();
	}
}
