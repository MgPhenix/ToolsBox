/*
Utils tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    /// RANDOM ///

    int32 random = GetRandomNumber(1, 4); // Get a random nbr between 1 & 4

    std::vector<float32> vector = { 3.0f, 1.0f, 0.5f };

    float32 random_from_vector = GetRandomValue(vector); // Get a random value from the vector

    /// Text ///

    std::string extension = GetPathExtension("C:/test/file.txt"); // Return ".txt" 

    std::string name = GetPathName("C:/test/file.txt"); // Return "file"

    std::string time = GetLocalTime(); // Return the local time in format -> hours:minutes:seconds

    /// ASSERT ///

    bool condition = true;
    ASSERT(condition); // If condition = false program will stop here and throw an exeption

    DEBUG_ASSERT(condition); // Same but will do nothing on Release (only work on Debug)

    /// CLAMP ///

    int a = 3;
    
    a = Clamp(a + 2, 2, 4); // Clamp say that a shoul be between 2 and 4,  because a + 2 = 5 it will return the maximum so 4

    return 0;
}