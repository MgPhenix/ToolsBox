#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

template<typename... Args>
struct ListenerV2
{
	ListenerID					 id;
	std::function<void(Args...)> func;
};

class IDispatcher
{
	virtual ~IDispatcher() = default;
};

template<typename... Args>
class DispatcherV2 : IDispatcher
{
private:

	std::vector<ListenerV2<Args...>> m_listeners;

public:

};




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

template<typename F>
void AddFunc(F&& func)
{
	using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;
	func_args<Sig>::Add(Sig(std::forward<F>(func)));
}

int calcul(int a, int b)
{
	return a + b;
}


template<typename... Args>
void Emit(Args&&... value)
{
	std::unordered_map<

	for (auto f : Dispatcher<Args...>::m_funcList)
	{
		f(std::forward<Args>(value)...);
	}
}

int main()
{
//	AddFunc([](int b) { std::cout << "Test : " << b << std::endl; });
//	
//	Emit(4);  // Print "Test : 4"



	return 0;
}