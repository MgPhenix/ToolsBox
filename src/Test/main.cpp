#include "include.h"
#include <iostream>


int main()
{
	Vector2f test(1.f, 2.f);
	test *= 2;
	std::cout << test.x << "/" << test.y << std::endl;

	return 0;
}