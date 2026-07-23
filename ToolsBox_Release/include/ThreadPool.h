#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>

/*
* @brief A Thread pool that stock inactive thread you can use for your task
*/
class ThreadPool
{
private:

	std::vector<std::thread>		  m_threads;
	std::queue<std::function<void()>> m_tasks;
	std::mutex						  m_mutex;
	std::condition_variable			  m_condition;
	bool							  m_stop;

public:

	explicit ThreadPool(size_t threadNbr);
	ThreadPool();
	~ThreadPool();

	void WorkerLoop();
	
	//NOT MADE BY ME CAUSE IDK HOW IT WORK (i will redo it later)
	template<typename F,typename... Args>
	auto Submit(F&& func, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
	{
		using ReturnType = std::invoke_result_t<F, Args...>; //NOTE FOR ME : invoke_result_t permet de get le type de retour de ses arguments 

		auto task = std::make_shared<std::packaged_task<ReturnType()>>(
			[f = std::forward<F>(func), //NOTE FOR ME : std::forward resautre ? L'etat d'origine Rvalue Ivalue
			args = std::make_tuple(std::forward<Args>(args)...)]() mutable { //NOTE FOR ME : make tuple en fait un tuple voila merci bcp | mutable = modifiable meme dans const
				return std::apply(f, args); //NOTE FOR ME : apply appelle la fonction "f" avec l'argument "args"
			}
		);

		std::future<ReturnType> futur = task->get_future();
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_stop)
				throw std::runtime_error("Programm Throw (up lol)");

			m_tasks.push([task]() { (*task)(); }); //NOTE FOR ME : On push packaged_task dans m_tasks
		}

		m_condition.notify_one();
		return futur;
	}
};