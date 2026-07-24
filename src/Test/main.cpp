#include "ToolsBox.h"
#include <iostream>
#include <functional>

template<typename F, typename... Args>
auto AutoConvertSubmission(F&& func, Args&&... args) -> std::function<std::invoke_result_t<F, Args...>()>
{
	using ReturnType = std::invoke_result_t<F, Args...>;

	return [f = std::forward<F>(func),
		args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
		return std::apply(f, args);
		};
}

int calcul(int a, int b)
{
	return a + b;
}

template<typename... Args>
std::vector<std::function<void(Args...)>> funcList;

int main()
{


	//auto test = Test(calcul, 4, 2);
	//auto truc = test();
	
	//std::cout << truc << std::endl;
	return 0;
}