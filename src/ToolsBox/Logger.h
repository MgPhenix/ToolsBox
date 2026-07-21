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
	
	static Logfile& GetInstance();

	bool IsFileOpen();

	void OpenFile(const std::string& path);
	void SaveInFile(const Log& log);
	void CloseFile();

	void LOG(Severity severity, const std::string& message);

	~Logfile();
};

