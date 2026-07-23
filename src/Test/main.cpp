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

int task1(int a) 
{
	//std::lock_guard<std::mutex> lock(mutex_score);
	std::cout << "Thread 1 is running. ID: " << std::this_thread::get_id() << "\n";
	score += a;
	return score + 10;
}

//auto task2() -> int
//{
//	//std::lock_guard<std::mutex> lock(mutex_score);
//	std::cout << "Thread 2 is running. ID: " << std::this_thread::get_id() << "\n";
//	score += 15;
//}

int main()
{
	//ThreadPool pool(4);

	//auto test = pool.Submit(task1, 10);

	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));

	//std::cout << "1 : " << score << std::endl;

	//int score2 = test.get();

	//std::cout << "1 : " << score << std::endl;
	//std::cout << "2 : " << score2 << std::endl;

	/*std::cout << "3 : " << score << std::endl;

	std::cout << "4 : " << score << std::endl;*/


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