/*
EventSystemV2 tuto
*/
#include <iostream>
#include "ToolsBox.h"

int main()
{
    EventSystemV2& ES = EventSystemV2::GetInstance();


    /// Subscribe/Emit ///

    ES.Subscribe("Test", [](int variable) {                        //Subribe to an evenement "Test"
        std::cout << "Number is " << variable << std::endl;        // When the evenement will be called this function will be execute with the parameter variable
    }); 

    ES.Emit("Test", 5); // Call all function that are subscribe to "Test" -> print "Number is 5" in the console


    /// Unsubscribe ///

    ListenerID id = ES.Subscribe("Event", []() {std::cout << "Hello" << std::endl; });
    ES.Unsubscribe("Event", id); // Unsubscribe the function from the evenement so the function won't be called when emit

    ES.Emit("Event"); // function is not called


    /// Subscribe Once ///

    ES.SubscribeOnce("Event 2", []() {std::cout << "Hello" << std::endl; }); // Same as Subscribe but will be auto unsubscribe when called
    
    ES.Emit("Event 2"); // Print "Hello" in the console

    ES.Emit("Event 2"); // Do nothing because function is unsubscribe


    /// Get Result ///

    ListenerID addition_id     = ES.Subscribe("Event 3", [](int a, int b) { return a + b; }); // This function will return a int
    ListenerID substraction_id = ES.Subscribe("Event 3", [](int a, int b) { return a - b; }); // This function will return a int
    
    Result<int> result = ES.Emit<int>("Event 3", 9, 3);       // Get the result map. You need to precise the type of result you want in Result and in Emit
    //     ^^^ Important         ^^^ Important

    std::cout << result[addition_id] << std::endl;            // Print 9 + 3 so 12 
    std::cout << result[substraction_id] << std::endl;        // Print 9 - 3 so 6 


    /// Clear ///

    ES.EraseEmiter("Event"); // Erase all function who was subscribed to "Even"

    ES.EraseAll();           // Erase everything from all event

    return 0;
}