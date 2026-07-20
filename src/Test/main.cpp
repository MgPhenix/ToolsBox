#include "include.h"
#include <iostream>
#include <fstream>
#include "Logger.h"

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
	Timer timer;
	float64 start = timer.Start();

	ListenerID test = EventSystem::GetInstance().SubscribeOnce("Test", [](const EventData& data) {std::cout << event_cast<int>(data) << std::endl; });

	EventSystem::GetInstance().Emit("Test", 4);
	//EventSystem::GetInstance().Unsubscribe("Test", test);
	EventSystem::GetInstance().Emit("Test", 9);
	EventSystem::GetInstance().ClearAll();
	
	Logfile logger;
	//logger.OpenFile("../../latest.log");
	logger.SaveInFile({ Severity::WARN,"12:00:00","Ceci est un deuxieme test" });

	float64 end = timer.End();

	std::cout << "Start : " << start << " | End : " << end << " | Time : " << end - start << std::endl;

	return 0;
}