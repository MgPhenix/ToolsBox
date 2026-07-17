#pragma once
#include "PrimitiveTypes.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

using ListenerID = uint32;

class EventSystem
{
private:

	struct Listener
	{
		ListenerID			  m_id;
		std::function<void()> m_func;

		Listener(ListenerID id, std::function<void()> func);
	};

	std::unordered_map<std::string, std::vector<Listener>> m_listeners;
	ListenerID	m_nextID = 0;

public:

	static EventSystem& GetInstance();

	ListenerID Subscribe	(const std::string& emiter, std::function<void()> func);
	ListenerID SubscribeOnce(const std::string& emiter, std::function<void()> func);
	void       Unsubscribe	(const std::string& emiter, ListenerID id);

	void Emit		(const std::string& emiter);
	void EraseEmiter(const std::string& emiter);
	void ClearAll	();
};