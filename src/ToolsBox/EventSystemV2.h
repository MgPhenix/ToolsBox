#pragma once
#include "Traits.h"
#include "Config.h"
#include "PrimitiveTypes.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

#ifdef CPP_14

using ListenerID = uint32;


/**
* @brief Struct that stock information from the listener like function to execute or the id
*/
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


	void Callback(Args&&... args)
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
struct func_args;

template<typename R, typename... Args>
struct func_args<std::function<R(Args...)>>
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


/**
* @brief An EventSystem where you can subscribe a listener to an event, the function of the listener will be executed when the event will be called
* @brief Better version of the normal EventSystem because he auto guess type of variable you pass and don't use std::any
*/
class EventSystemV2
{
private:

	std::unordered_map<std::string, IDispatcher*> m_dispatcher;
	ListenerID m_nextID = 0;

public:

	/**
	* @brief Return the singelton instance of EventSystem
	*/
	static EventSystemV2& GetInstance()
	{
		static EventSystemV2 instance;
		return instance;
	}

	/**
	* @brief Subscribe to an event, when this event will be called the function you provided will be executed
	* @param string emiter : event you want to subscribe to
	* @tparam F function : Function that will be called, take any argument just be sure that it will match the Emiter value
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	template<typename F>
	ListenerID Subscribe(const std::string& emiter, F&& func)
	{
		ListenerID id = m_nextID++;
		using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;

		IDispatcher* dispatcher = nullptr;

#ifdef CPP_20
		if (!m_dispatcher.contains(emiter))
#else
		if (!m_dispatcher.count(emiter))
#endif
			dispatcher = m_dispatcher[emiter];

		m_dispatcher[emiter] = func_args<Sig>::AddFunc(Sig(std::forward<F>(func)), dispatcher, id);
		return id;
	}

	/**
	* @brief Same as Subscribe() but will auto unsubscribe when function is called for the first time
	* @param string emiter : event you want to subscribe to
	* @tparam F function : Function that will be called, take any argument just be sure that it will match the Emiter value
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	template<typename F>
	ListenerID SubscribeOnce(const std::string& emiter, F&& func)
	{
		ListenerID id = m_nextID++;
		using Sig = typename lambda_function_traits<std::decay_t<F>>::signature;

		IDispatcher* dispatcher = nullptr;

#ifdef CPP_20
		if (!m_dispatcher.contains(emiter))
#else
		if (!m_dispatcher.count(emiter))
#endif
			dispatcher = m_dispatcher[emiter];

		m_dispatcher[emiter] = func_args<Sig>::AddFunc(Sig(
			[emiter, id, this, function = std::forward<F>(func)](auto&&... args)
			{
				function(std::forward<decltype(args)>(args)...);
				Unsubscribe(emiter, id);
			}
		), dispatcher, id);
		return id;
	}

	/**
	* @brief Unsubscribe from an event
	* @param string emiter : The event your listener is subscribe to
	* @param ListenerID	: Your listener ID, you can get it when you use Subscribe() or SubscribeOnce()
	*/
	void Unsubscribe(const std::string& emiter, ListenerID id)
	{
#ifdef CPP_20
		if (!m_dispatcher.contains(emiter))
#else
		if (!m_dispatcher.count(emiter))
#endif
			return;

		m_dispatcher[emiter]->DeleteOne(id);
	}

	/**
	* @brief Emit an event with arguments, all function that are subscribe to this event will be called with this arguments
	* @param string emiter : the event you want to emit
	* @tparam Args... args : parameter that all function will take, can be anything
	*/
	template<typename... Args>
	void Emit(const std::string& emiter, Args... args)
	{
		if (!m_dispatcher.contains(emiter))
			return;

		static_cast<DispatcherV2<void, Args...>*>(m_dispatcher[emiter])->Callback(std::forward<Args>(args)...);
	}

	/**
	* @brief Erase all listener from an emiter
	* @param string emiter : the emiter you want to erase
	*/
	void EraseEmiter(const std::string& emiter)
	{
#ifdef CPP_20
		if (!m_dispatcher.contains(emiter))
#else
		if (!m_dispatcher.count(emiter))
#endif
			return;

		delete m_dispatcher[emiter];
		m_dispatcher.erase(emiter);
	}

	/**
	*@brief Clear all listener from all emiter that exists
	*/
	void EraseAll()
	{
		for (auto& pair : m_dispatcher)
			delete pair.second;

		m_dispatcher.clear();
	}
};

#endif // CPP_14