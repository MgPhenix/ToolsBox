#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

template<typename K, typename V>
struct Node
{
	K key;
	V value;
	Node* next;
};


template<typename K, typename V, typename Allocator = MyAllocator<Node<K, V>>>
class MyUnorderedMap
{
private:
	
	std::vector<Node<K, V>*> buckets;
	Allocator			  allocator;
	size_t				  bucket_count = 8;

public:
	
	MyUnorderedMap() : 
		buckets(8, nullptr) 
	{
	}

	void TempAdd(Node<K, V>* truc) 
	{ 
		buckets[std::hash<K>{}(truc->key) % 8] = truc;
	}

	V* find(const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
				return &current->value;
			current = current->next;
		}

		return nullptr;
	}

	V* operator[](const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
				return &current->value;
			current = current->next;
		}

		return nullptr;
	}
};



int main()
{
	MyUnorderedMap<std::string, int> map;
	map.TempAdd(new Node<std::string, int>(std::string("test"), 5, nullptr));
	int* test = map["test"];
	if(test != nullptr)
		std::cout << *test << std::endl;
}










//MyAllocator<float> alloc;

//using ReboundAllocType = MyAllocator<float>::rebind<Node>::other;
//ReboundAllocType allocNode;

//Node* n = allocNode.allocate(1);
//new (n) Node{ 42, 3.14f };

//std::cout << "Key : " << n->key << " | Value : " << n->value << std::endl;
//n->~Node();
//allocNode.deallocate(n, 1);
//return 0;


//int main()
//{
//	Test* mem = static_cast<Test*>(::operator new(3 * sizeof(Test)));
//
//	std::cout << mem[0].x << std::endl; //Print n'importe quoi 
//
//	new (&mem[0]) Test();
//
//	std::cout << mem[0].x << std::endl; //Print n'importe quoi 
//
//	mem[0].~Test();
//
//	::operator delete(mem);
//
//
//	return 0;
//}