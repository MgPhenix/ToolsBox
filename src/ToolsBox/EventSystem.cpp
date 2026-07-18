#include "EventSystem.h"

EventSystem& EventSystem::GetInstance()
{
	static EventSystem instance;
	return instance;
}

ListenerID EventSystem::Subscribe(const std::string& emiter, std::function<void(const EventData&)> func)
{
	ListenerID id = m_nextID++;
	m_listeners[emiter].push_back({ id, std::move(func)});
	return id;
}

ListenerID EventSystem::SubscribeOnce(const std::string& emiter, std::function<void(const EventData&)> func)
{
	ListenerID id = m_nextID++;
	m_listeners[emiter].push_back({ id, [emiter, id, function = std::move(func)](const EventData& data) {
		function(data);
		EventSystem::GetInstance().Unsubscribe(emiter, id);
	}});
	
	return id;
}

void EventSystem::Unsubscribe(const std::string& emiter, ListenerID id)
{
	if (!m_listeners.contains(emiter))
		return;

	m_listeners[emiter].erase(std::remove_if(
		m_listeners[emiter].begin(),
		m_listeners[emiter].end(),
		[id](const Listener& l) { return l.m_id == id; }),
		m_listeners[emiter].end()
	);
}

void EventSystem::Emit(const std::string& emiter, const EventData& data)
{
	for (auto& listener : m_listeners[emiter])
		listener.m_func(data);
}

void EventSystem::EraseEmiter(const std::string& emiter)
{
	m_listeners.erase(emiter);
}

void EventSystem::ClearAll()
{
	m_listeners.clear();
}

//EventSystem::Listener::Listener(ListenerID id, std::function<void()> func) :
//	m_id(id),
//	m_func(func)
//{}
