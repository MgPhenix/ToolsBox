#pragma once
#include "Traits.h"
#include "PrimitiveTypes.h"

template<typename... Args>
struct Dispatcher
{
	inline static std::vector<std::function<void(Args...)>> m_funcList;
};

template<typename T>
struct func_args;

template<typename R, typename... Args>
struct func_args<std::function<R(Args...)>>
{
	static void Add(std::function<R(Args...)> f)
	{
		Dispatcher<Args...>::m_funcList.push_back(std::move(f));
	}
};

using ListenerID = uint32;


class EventSystemV2
{
private:

	//std::vector<Dispatcher*> m_list;

public:

	static EventSystemV2& GetInstance()
	{
		static EventSystemV2 instance;
		return instance;
	}

	template<typename F>
	void AddFunc(F&& func)
	{
		using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;
		func_args<Sig>::Add(Sig(std::forward<F>(func)));
	}

	template<typename... Args>
	void Emit(Args&&... value)
	{
		for (auto f : Dispatcher<Args...>::m_funcList)
		{
			f(std::forward<Args>(value)...);
		}
	}
};

