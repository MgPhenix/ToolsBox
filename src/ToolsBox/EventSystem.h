#pragma once
#include "PrimitiveTypes.h"
#include "Config.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

using ListenerID = uint32;

#ifdef CPP_17

	#include <any>
	using EventData = std::any;

	/**
	* @brief Cast an EventData to the type T you want
	*/
	template<typename T>
	T event_cast(const EventData& data)
	{
		return std::any_cast<T>(data);
	}

#else
	using EventData = void;
	/**
	* @brief Cast nothing to nothing so don't use it. 
	* @brief This function is unuseable because you don't have minimum c++17 so don't use it or change your version you dumbass
	*/
	template<typename T>
	T event_cast()
	{
		return void();
	}
#endif


/*
* @brief An EventSystem where you can subscribe a listener to an event, the listener will be called when the event will be called
* @brief If you use c++ >=17 you have access to EventData(any) who can stock a context for the listener
*/
class EventSystem
{
private:

	struct Listener
	{
		ListenerID m_id;

#ifdef CPP_17
		std::function<void(const EventData&)> m_func;
#else
		std::function<void()> m_func;
#endif

	};

private:

	std::unordered_map<std::string, std::vector<Listener>> m_listeners;
	ListenerID	m_nextID = 0;

public:

	/**
	* @brief Return the singelton instance of EventSystem
	*/
	static EventSystem& GetInstance();

#ifdef CPP_17
	/**
	* @brief Subscribe to an event, when this event will be called the function you provided will be executed
	* @param string emiter : event you want to subscribe to
	* @param function : Function that will be called. Take an EventData(any) as parameter for provide context (use event_cast<your_type>(data) in your function )
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	ListenerID Subscribe(const std::string& emiter, std::function<void(const EventData&)> func);
	/**
	* @brief Same as Subscribe() but will auto unsubscribe when function is called
	* @param string emiter : event you want to subscribe to
	* @param function : Function that will be called. Take an EventData(any) as parameter for provide context (use event_cast<your_type>(data) in your function )
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void(const EventData&)> func);
#else
	/**
	* @brief Subscribe to an event, when this event will be called the function you provided will be executed
	* @param string emiter : event you want to subscribe to
	* @param function : Function that will be called.
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	ListenerID Subscribe(const std::string& emiter, std::function<void()> func);
	/**
	* @brief Same as Subscribe() but will auto unsubscribe when function is called
	* @param string emiter : event you want to subscribe to
	* @param function : Function that will be called.
	* @return ListenerID : ID of the listener you juste created (usefull for unsubscribe)
	*/
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void()> func);
#endif
	
	/**
	* @brief Unsubscribe from an event 
	* @param string emiter : The event your listener is subscribe to
	* @param ListenerID	: Your listener ID, you can get it when you use Subscribe() or SubscribeOnce()
	*/
	void Unsubscribe(const std::string& emiter, ListenerID id);

#ifdef CPP_17
	/**
	* @brief Emit an event with an EventData context, all function that are subscribe to this event will be called with this context
	* @param string emiter : the event you want to emit
	* @param EventData(any) : parameter that all function will take can be anything (only available with c++ 17+)
	*/
	void Emit(const std::string& emiter, const EventData& data = 0);
#else
	/**
	* @brief Emit an event, all function that are subscribe to this event will be called
	* @param string emiter : the event you want to emit
	*/
	void Emit(const std::string& emiter);
#endif

	/**
	* @brief Erase all listener from an emiter 
	* @param string emiter : the emiter you want to erase
	*/
	void EraseEmiter(const std::string& emiter);
	/**
	*@brief Clear all listener from all emiter that exists
	*/
	void ClearAll	();
};