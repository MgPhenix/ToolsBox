#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

struct Log
{
	Severity	m_severity;
	std::string m_time;
	std::string m_message;

	void PrintLog();
};

class Logfile
{
private:

	std::ofstream m_file;

public:
	
	Logfile& GetInstance()
	{
		static Logfile instance;
		return instance;
	}

	void OpenFile(const std::string& path);
	void SaveInFile(const Log& log);
	void CloseFile();

	~Logfile();
};

