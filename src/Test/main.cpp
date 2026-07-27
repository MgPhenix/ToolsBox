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
public:
	virtual ~IDispatcher() = default;

	virtual void DeleteOne(ListenerID id) {};
};

template<typename R, typename... Args>
class DispatcherV2 : public IDispatcher
{
private:

	std::vector<ListenerV2<Args...>> m_listeners;

public:

	void Add(std::function<R(Args...)> func, ListenerID id)
	{
		m_listeners.push_back({ id, std::move(func) });
	}
	
	
	void Call(Args&&... args)
	{
		for (auto& listener : m_listeners)
		{
			listener.func(args...);
		}
	}
	
	void DeleteOne(ListenerID id) override
	{
		m_listeners.erase(std::remove_if(
			m_listeners.begin(),
			m_listeners.end(),
			[id](const ListenerV2<Args...>& l) { return l.id == id; }),
			m_listeners.end()
		);
	}

	~DispatcherV2()
	{
		m_listeners.clear();
	}

};
template<typename T>
struct func_args_test;


template<typename R, typename... Args>
struct func_args_test<std::function<R(Args...)>>
{
	static IDispatcher* AddFunc(std::function<R(Args...)> func, IDispatcher* idispatcher, ListenerID id)
	{
		DispatcherV2<R, Args...>* dispatcher = nullptr;

		if (idispatcher == nullptr)
			dispatcher = new DispatcherV2<R, Args...>;
		else
			dispatcher = static_cast<DispatcherV2<R, Args...>*>(idispatcher);

		dispatcher->Add(std::move(func), id);

		return dispatcher;
	}
};

class EventTest
{
private:

	std::unordered_map<std::string, IDispatcher*> m_dispatcher;
	ListenerID m_nextID = 0;

public:

	template<typename F>
	ListenerID Subscribe(const std::string& emiter, F&& func)
	{
		ListenerID id = m_nextID++;
		using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;
		
		IDispatcher* dispatcher = nullptr;

		if (m_dispatcher.contains(emiter))
			dispatcher = m_dispatcher[emiter];

		m_dispatcher[emiter] = func_args_test<Sig>::AddFunc(Sig(std::forward<F>(func)), dispatcher, id);
		return id;
	}

	void Unsubscribe(const std::string& emiter, ListenerID id)
	{
		if (!m_dispatcher.contains(emiter))
			return;

		m_dispatcher[emiter]->DeleteOne(id);
	}

	template<typename... Args>
	void Emit(const std::string& emiter,Args... args)
	{
		if (!m_dispatcher.contains(emiter))
			return;

		static_cast<DispatcherV2<void, Args...>*>(m_dispatcher[emiter])->Call(std::forward<Args...>(args...));
	}
};


int main()
{
	EventTest test;

	ListenerID bonjour = test.Subscribe("test", [](int a) { std::cout << a << std::endl; });
	//ListenerID bonjour2 = test.Subscribe("test", [](int b) { return 0; });
	test.Emit("test", 5);

	test.Unsubscribe("test", bonjour);

	test.Emit("test", 6);

	return 0;
}


//template<typename... Args>
//struct Dispatcher
//{
//	inline static std::vector<std::function<void(Args...)>> m_funcList;
//};
//
//template<typename T>
//struct func_args;
//
//template<typename R, typename... Args>
//struct func_args<std::function<R(Args...)>>
//{
//	static void Add(std::function<R(Args...)> f)
//	{
//		Dispatcher<Args...>::m_funcList.push_back(std::move(f));
//	}
//};
//
//template<typename F>
//void AddFunc(F&& func)
//{
//	using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;
//	func_args<Sig>::Add(Sig(std::forward<F>(func)));
//}
