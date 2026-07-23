/*
Object Pool Tuto
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
    ObjectPool<Object> pool(40); // Allocate 40 object

    Object* obj = pool.GetInactiveObject(); // Get an inactive object, so because we allocate 40 object there is now 39 inactives object and 1 active

    obj->PrintTest();

    pool.ReleaseObject(obj); //Object is released and marked inactive so now we have 40 inactives object, Don't forget to release object when you don't need it anymore

    std::vector<Object*> obj_list = pool.GetInactivesObjects(10); // Get 10 inactives object if possible (can give less if you don't have enough inactives object in the pool)

    
    return 0;

} // ObjectPool and alla allocate object are auto destroy when you leave the scope