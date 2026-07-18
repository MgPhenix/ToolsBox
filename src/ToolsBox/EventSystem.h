#pragma once
#include "PrimitiveTypes.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>
#include <any>

using ListenerID = uint32;
using EventData = std::any;

template<typename T>
T event_cast(const EventData& data)
{
	return std::any_cast<T>(data);
}


class EventSystem
{
private:

	struct Listener
	{
		ListenerID			  m_id;
		std::function<void(const EventData&)> m_func;

		//Listener(ListenerID id, std::function<void()> func);
	};

	std::unordered_map<std::string, std::vector<Listener>> m_listeners;
	ListenerID	m_nextID = 0;

public:

	static EventSystem& GetInstance();

	ListenerID Subscribe	(const std::string& emiter, std::function<void(const EventData&)> func);
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void(const EventData&)> func);
	void       Unsubscribe	(const std::string& emiter, ListenerID id);

	void Emit		(const std::string& emiter, const EventData& data);
	void EraseEmiter(const std::string& emiter);
	void ClearAll	();
};