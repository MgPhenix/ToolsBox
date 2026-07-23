/*
Profiler tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    {
        SCOPE_PROFILER("DEBUG_NAME");
    } //When the scope end the profiler will write in the consol the time it take for him to execute this scope

    {
        SCOPE_PROFILER("TEST");
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Because we sleep for 2seconde the scope profiler will write in the console ~2000ms (not exact because windows suck) 
    }

      

    return 0;
}