/**
* @file Logger.h
* @brief Save & Manager log, don't use directlty instead use macro LOG_XXX(message) lile LOG_INFO(message)
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

/**
* @brief Log data struct store :
* @brief -Severity
* @brief -time
* @brief -message
*/
struct Log
{
	Severity	m_severity;
	std::string m_time;
	std::string m_message;

	/**
	* @brief PrintFormat : [hours:minutes:seconds][Severity] : message
	*/
	void PrintLog();
};

/**
* @brief LogSystem, write in a file all log that are provided with the function LOG_XXX(message) like LOG_INFO(message)
* @brief Before using it open the file with Logfile::OpenFile(path)
* @brief -Use .log file for better understanding but it's optional
*/
class Logfile
{
private:

	std::ofstream m_file;

public:
	/**
	* @brief Return the singelton instance of Logfile
	*/
	static Logfile& GetInstance();

	/*
	* @return boolean, true if file is open, false is not
	*/
	bool IsFileOpen();

	/**
	* @brief Open a file for write log in it
	* @brief -Use .log file for better understanding but it's optional
	* @param string : path of your file
	*/
	void OpenFile(const std::string& path);
	/**
	* @brief Save a log in the file if this one is open
	* @brief Auto called by LOG_XXX(message) function
	* @param Log : the log you want to save
	*/
	void SaveInFile(const Log& log);
	/**
	* @brief Close the file if one was open
	* @brief The destructor of Logfile auto call this function
	*/
	void CloseFile();

	/**
	* @brief Print and save a log 
	* @brief Please do not use, instead use LOG_XXX(message) function
	*/
	void LOG(Severity severity, const std::string& message);

	~Logfile();
};