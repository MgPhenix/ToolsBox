/*
Thread Pool tuto
*/
#include <iostream>
#include "ToolsBox.h"

int Task(int a, int b)
{
    return a + b;
}


int main()
{
    ThreadPool pool(4); // We create 4 thread that we can use for multithred our programm, if you don't specify the thread number it will automaticaly take as much as he can -1 (for main thread)

    auto future = pool.Submit(Task, 5, 3); // We ask a inactive thread to execute the function

    int result = future.get(); // If the thread finished the task, he return the value if not program wait until the thread finish

    std::cout << result << std::endl;

    return 0;
}