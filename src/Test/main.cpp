#include "include.h"
#include <iostream>
#include <fstream>

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
	//{
	//	UniquePtr<Test> test(new Test(8));

	//	test->PrintOui();
	//}
	//AssetEngine AE;
	//AE.LoadFile("../../test.gcle", "GCLE");

	SharedPtr<Test> test(new Test(9));
	std::cout << test.GetCount() << std::endl;
	
	{
		SharedPtr<Test> test2 = test;
		std::cout << test2.GetCount() << std::endl;
	}
		
	std::cout << test.GetCount() << std::endl;

	return 0;
}