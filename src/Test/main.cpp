#include "include.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <mutex>

class Test
{
private: 
	int oui = 0;
public:
	Test(int oui) : oui(oui) {};
	void PrintOui() { std::cout << oui << std::endl; };
};

int score = 0;
std::mutex mutex_score;

void task1() 
{
	std::lock_guard<std::mutex> lock(mutex_score);
	std::cout << "Thread 1 is running. ID: " << std::this_thread::get_id() << "\n";
	score += 10;
}

void task2() 
{
	std::lock_guard<std::mutex> lock(mutex_score);
	std::cout << "Thread 2 is running. ID: " << std::this_thread::get_id() << "\n";
	score += 15;
}

int main()
{
	std::thread t1(task1);

	std::cout << "1 : " << score << std::endl;

	std::thread t2(task2);

	std::cout << "t1 ID: " << t1.get_id() << "\n";
	std::cout << "t2 ID: " << t2.get_id() << "\n";

	std::cout << "2 : " << score << std::endl;

	if (t1.joinable()) {
		t1.join();
		std::cout << "t1 joined\n";
	}

	std::cout << "3 : " << score << std::endl;

	if (t2.joinable()) {
		t2.join();
		std::cout << "t2 joined\n";
	}

	std::cout << "4 : " << score << std::endl;



	//std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//EventSystem& ES = EventSystem::GetInstance();

	//ES.Subscribe("test", [](const EventData& data) { std::cout << "test" << event_cast<int>(data) << std::endl; });

	//ES.Emit("test", 43);

	//Timer timer;
	//float64 start = timer.Start();

	//Logfile& logger = Logfile::GetInstance();
	//logger.OpenFile("../../latest.log");

	//logger.SaveInFile({ Severity::WARN,"18:00:00","Ceci est un deuxieme test" });

	//float64 end = timer.End();

	//std::cout << "Start : " << start << " | End : " << end << " | Time : " << end - start << std::endl;

	return 0;
}