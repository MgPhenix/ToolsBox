#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>


int main()
{
	EventSystemV2& test = EventSystemV2::GetInstance();

	ListenerID bonjour = test.SubscribeOnce("test", [](int a, int b) { std::cout << a + b << std::endl; });
	//ListenerID bonjour2 = test.Subscribe("test", [](int b) { return 0; });
	test.Emit("test", 5, 7);
	//test.Unsubscribe("test", bonjour);

	test.Emit("test",9, 8);

	return 0;
}