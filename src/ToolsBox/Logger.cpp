#include "Logger.h"

void Log::PrintLog()
{
	std::cout << "[" << m_time << "]" << "[" << SevertityToString(m_severity) << "]" << " : " << m_message << std::endl;
}

void Logfile::OpenFile(const std::string& path)
{
	m_file = std::ofstream(path);
}

void Logfile::SaveInFile(const Log& log)
{
	if (!m_file)
	{
		std::cout << "File is not open please use OpenFile before using this function " << std::endl;
		return;
	}

	std::string line;
	line += "[" + log.m_time + "]";
	line += "[" + SevertityToString(log.m_severity) + "]";
	line += " : " + log.m_message;

	m_file.write(line.c_str(), line.size());
}

void Logfile::CloseFile()
{
	m_file.close();
}

Logfile::~Logfile()
{
	CloseFile();
}
