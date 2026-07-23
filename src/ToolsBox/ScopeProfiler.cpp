#include "ScopeProfiler.h"
#include <iostream>

ScopeProfiler::ScopeProfiler(const std::string& name) :
	m_name(name)
{
	m_timer.Start();
}

ScopeProfiler::~ScopeProfiler()
{
	std::cout << "[ScopeProfiler][" << m_name << "] : " << m_timer.GetTime() << " ms" << std::endl;
}
