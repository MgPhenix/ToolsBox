#pragma once
#include <string>
#include "Timer.h"

/**
* @brief Print the time that the scope take to execute
* @param string : name of your task
*/
class ScopeProfiler
{
private:

	std::string m_name;
	Timer		m_timer;

public:
	ScopeProfiler(const std::string& name);
	~ScopeProfiler();
};