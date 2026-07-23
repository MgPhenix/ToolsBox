/*
Timer tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    Timer timer;

    float32 start = timer.Start(); // start timer

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Wait 1 seconde

    float32 end = timer.End(); // End timer here
    
    float32 time = end - start; // Should be ~1000 ms 

    std::cout << time << " ms passed" << std::endl;

    return 0;
}