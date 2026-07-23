/*
Log tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    OPEN_FILE("latest.log"); // Open a file for write log

    LOG_INFO("Message"); // Will write in the console and in the file [hours:minutes:seconds][INFO] : message
    /* Variants: 
    
    LOG_WARN
    LOG_ERROR
    LOG_CRITICAL
    */

    LOG_DEBUG("Message Debug"); // Same but will do nothing on release (only work in debug)

    CLOSE_FILE; // Close the file (file will auto close at the end at the program if you don't do it


    return 0;
}