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

	template<typename T>
	T event_cast(const EventData& data)
	{
		return std::any_cast<T>(data);
	}

#else
	using EventData = void;

	template<typename T>
	T event_cast()
	{
		return void();
	}
#endif



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

	std::unordered_map<std::string, std::vector<Listener>> m_listeners;
	ListenerID	m_nextID = 0;

public:

	static EventSystem& GetInstance();

#ifdef CPP_17
	ListenerID Subscribe	(const std::string& emiter, std::function<void(const EventData&)> func);
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void(const EventData&)> func);
#else
	ListenerID Subscribe	(const std::string& emiter, std::function<void()> func);
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void()> func);
#endif
	
	void       Unsubscribe	(const std::string& emiter, ListenerID id);

#ifdef CPP_17
	void Emit		(const std::string& emiter, const EventData& data);
#else
	void Emit		(const std::string& emiter);
#endif

	void EraseEmiter(const std::string& emiter);
	void ClearAll	();
};