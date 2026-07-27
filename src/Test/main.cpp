#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>


int main()
{
	EventSystemV2& ES = EventSystemV2::GetInstance();

	ListenerID ID = ES.Subscribe("test", [](int a, int b) { return a + b; });

	Result<int> result_test = ES.Emit<int>("test", 5, 7);

	std::cout << result_test[ID] << std::endl; // Affiche 5 + 7 donc 12

	return 0;
}