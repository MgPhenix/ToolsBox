#include "include.h"
#include <iostream>
#include <fstream>
#include <ctime>

class Test
{
private: 
	int oui = 0;
public:
	Test(int oui) : oui(oui) {};
	void PrintOui() { std::cout << oui << std::endl; };
};


int main()
{
	EventSystem& ES = EventSystem::GetInstance();

	ES.Subscribe("test", [](const EventData& data) { std::cout << "test" << event_cast<int>(data) << std::endl; });

	ES.Emit("test", 43);

	//Timer timer;
	//float64 start = timer.Start();

	//Logfile& logger = Logfile::GetInstance();
	//logger.OpenFile("../../latest.log");

	//logger.SaveInFile({ Severity::WARN,"18:00:00","Ceci est un deuxieme test" });

	//float64 end = timer.End();

	//std::cout << "Start : " << start << " | End : " << end << " | Time : " << end - start << std::endl;

	return 0;
}