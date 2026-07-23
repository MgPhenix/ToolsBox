/*
EventSystem tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    EventSystem& ES = EventSystem::GetInstance();


    /// Subscribe/Emit ///

    ES.Subscribe("Test", [](const EventData& data) {                        //Subribe to an evenement "Test"
        std::cout << "Number is " << event_cast<int>(data) << std::endl;    // When the evenement will be called this function will be execute with the parameter data
    }); 

    ES.Emit("Test", 5); // Call all function that are subscribe to "Test" -> print "Number is 5" in the console


    /// Unsubscribe ///

    ListenerID id = ES.Subscribe("Event", [](const EventData& data) {std::cout << "Hello" << std::endl; });
    ES.Unsubscribe("Event", id); // Unsubscribe the function from the evenement so the function won't be called when emit

    ES.Emit("Event"); // function is not called


    /// Subscribe Once ///

    ES.SubscribeOnce("Event 2", [](const EventData& data) {std::cout << "Hello" << std::endl; }); // Same as Subscribe but will be auto unsubscribe when called
    
    ES.Emit("Event 2"); // Print "Hello" in the console

    ES.Emit("Event 2"); // Do nothing because function is unsubscribe


    /// Clear ///


    ES.EraseEmiter("Event"); // Erase all function who was subscribed to "Even"

    ES.ClearAll(); // Erase everything from all event

    return 0;
}