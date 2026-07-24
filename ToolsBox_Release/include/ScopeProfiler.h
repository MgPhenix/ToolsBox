/**
* @file ScopeProfiler.h
* @brief Scope profiler that get the time a scope take to execute
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <string>
#include "Timer.h"

/**
* @brief Print the time that the scope take to execute
* @brief Don't use it directly use macro SCOPE_PROFILER(name) instead
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