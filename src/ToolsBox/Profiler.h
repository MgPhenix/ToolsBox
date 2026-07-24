/**
* @file Profiler.h
* @brief A Profiler for get the time that a task take to execute (still WIP)
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "Timer.h"
#include <unordered_map>
#include <string>

/**
* @brief stock all info a task need to have
*/
struct Task
{
	Timer		timer;
	std::string name;
	float32		start;
};

/**
* @brief Profiler class to mesure time that task take
*/
class Profiler
{
private:

	static std::unordered_map<std::string, Task> m_tasks;

public:
	/**
	* @brief Create a new task that will be mesure
	* @param std::string id : id of your task
	* @param std::string name : name that will be dysplay (for now it's not)
	*/
	static void NewTask(std::string id, std::string name = "");
	/**
	* @brief End a task and stop the timer
	* @param std::string id : id of your task
	*/
	static void EndTask(std::string id);
	/**
	* @brief Get Time a task has take
	* @param std::string id : id of your task
	* @return float32 : Time since the task started in milliseconds
	*/
	static float32 GetTask(std::string id);
};