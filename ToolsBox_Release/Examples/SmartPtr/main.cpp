/*
SmarPtr tuto
*/
#include <iostream>
#include "ToolsBox.h"

class Object
{
public:
    void PrintTest()
    {
        std::cout << "Test" << std::endl;
    }
};

int main()
{
    /// UniquePtr ///


    {
        UniquePtr<Object> ptr(new Object()); // A unique ptr is a ptr that will be auto destroy when the scope end
        ptr->PrintTest();
    } // Unique ptr is auto destroy here



    /// SharedPtr ///


    {
        SharedPtr<Object> shared_ptr(new Object()); // A SharedPtr do the same thing than a UniquePtr but he only destroy himself when he has 0 usage

        std::cout << shared_ptr.GetCount() << std::endl; // Return the number of SharedPtr that share the same pointer so here 1

        {
            SharedPtr<Object> second_shared(shared_ptr); // We create a new ptr that is the same as the first
            second_shared->PrintTest();

            std::cout << shared_ptr.GetCount() << std::endl; // Return 2 cause there is 2 shared ptr who share the same pointer

        } // second_shared is destroy here

        std::cout << shared_ptr.GetCount() << std::endl; // Because second_shared is destroy return 1 
    
    } // We leave the scope so shared_ptr is destroy and count is 0 so the pointer destroy himself


    return 0;
}