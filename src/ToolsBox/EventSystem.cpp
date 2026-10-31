#include "EventSystem.h"
#include <algorithm>

EventSystemOld& EventSystemOld::GetInstance()
{
	static EventSystemOld instance;
	return instance;
}

#ifdef CPP_17
ListenerID EventSystemOld::Subscribe(const std::string& emiter, std::function<void(const EventData&)> func)
#else
ListenerID EventSystem::Subscribe(const std::string& emiter, std::function<void()> func)
#endif
{
	ListenerID id = m_nextID++;
	m_listeners[emiter].push_back({ id, std::move(func)});
	return id;
}

#ifdef CPP_17
ListenerID EventSystemOld::SubscribeOnce(const std::string& emiter, std::function<void(const EventData&)> func)
#else
ListenerID EventSystem::SubscribeOnce(const std::string& emiter, std::function<void()> func)
#endif
{
	ListenerID id = m_nextID++;

#ifdef CPP_17
	m_listeners[emiter].push_back({ id, [emiter, id, function = std::move(func)](const EventData& data) {
		function(data);
		EventSystemOld::GetInstance().Unsubscribe(emiter, id);
	}});
#else
	m_listeners[emiter].push_back({ id, [emiter, id, function = std::move(func)]() {
	function();
	EventSystem::GetInstance().Unsubscribe(emiter, id);
} });
#endif

	return id;
}

void EventSystemOld::Unsubscribe(const std::string& emiter, ListenerID id)
{
#ifdef CPP_20
	if (!m_listeners.contains(emiter))
#else
	if (!m_listeners.count(emiter))
#endif
		return;

	m_listeners[emiter].erase(std::remove_if(
		m_listeners[emiter].begin(),
		m_listeners[emiter].end(),
		[id](const Listener& l) { return l.m_id == id; }),
		m_listeners[emiter].end()
	);
}
#ifdef CPP_17
void EventSystemOld::Emit(const std::string& emiter, const EventData& data)
{
	for (auto& listener : m_listeners[emiter])
		listener.m_func(data);
}
#else
void EventSystem::Emit(const std::string& emiter)
{
	for (auto& listener : m_listeners[emiter])
		listener.m_func();
}
#endif

void EventSystemOld::EraseEmiter(const std::string& emiter)
{
	m_listeners.erase(emiter);
}

void EventSystemOld::ClearAll()
{
	m_listeners.clear();
}