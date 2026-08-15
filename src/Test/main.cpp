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
	
	Node(K k, V v, Node* node) : 
		key(k),
		value(v),
		next(node) {}
};


template<typename K, typename V, typename Allocator = MyAllocator<Node<K, V>>>
class MyUnorderedMap
{
private:
	
	vector_l<Node<K, V>*> buckets;
	Allocator			  allocator;
	size_t				  bucket_count = 8;

public:
	
	MyUnorderedMap() : buckets(8, nullptr) {}

	~MyUnorderedMap()
	{
		for (auto& bucket : buckets)
		{
			Node<K, V>* current = bucket;
			while (current != nullptr)
			{
				Node<K, V>* next = current->next;

				current->~Node();
				allocator.deallocate(current, 1);
				current = next;
			}
		}
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

	void insert(K key, V value)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		if (current != nullptr)
		{
			while (current->next != nullptr)
			{
				if (current->next->key == key)
					return;
				current = current->next;
			}
		}

		Node<K,V>* newNode = allocator.allocate(1);
		new (newNode) Node<K, V>(std::move_if_noexcept(key), std::move_if_noexcept(value), nullptr);

		if(current == nullptr)
			buckets[index] = newNode;
		else
			current->next = newNode;
	}

	V& operator[](const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
				return current->value;
			current = current->next;
		}
	}

	MyUnorderedMap(const MyUnorderedMap& other) :
		bucket_count(other.bucket_count),
		buckets(other.bucket_count, nullptr)
	{
	//	for (auto& bucket : other.buckets)
	//	{
	//		if (bucket == nullptr)
	//			continue;

	//		Node<K, V>* other_current = bucket;

	//		size_t index = std::hash<K>{}(other_current->key) % other.bucket_count;
	//		Node<K,V>* current = buckets[index];
	//		new (buckets[index]) Node<K, V>(other_current);

	//		while (other_current != nullptr)
	//		{
	//			Node<K, V>* next = other_current->next;
	//			new (current->next) Node<K, V>(next);
	//			other_current = next;
	//		}
	//	}
	}

	MyUnorderedMap(MyUnorderedMap&& other)
	{

	}

	MyUnorderedMap& operator=(const MyUnorderedMap& other);

	MyUnorderedMap& operator=(MyUnorderedMap&& other);
};



int main()
{

	MyUnorderedMap<std::string, int> map;
	map.TempAdd(new Node<std::string, int>(std::string("test"), 5, nullptr));
	int test = map["test"];
	std::cout << test << std::endl;

	std::string truc = "truc";
	map.insert(truc, 8);
	int test2 = map["truc"];
	std::cout << test2 << std::endl;
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