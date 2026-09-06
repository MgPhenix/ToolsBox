#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

template<typename F, typename S>
struct Pair
{
	F first;
	S second;
};

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

	Node(const Node& other) :
		key(other.key),
		value(other.value),
		next(other.next)
	{}

	Node(Node&& other) :
		key(other.key),
		value(other.value),
		next(other.next)
	{
		other.next = nullptr;
	}
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

		std::cout << "Value not found" << std::endl;
	}

	MyUnorderedMap(const MyUnorderedMap& other) :
		bucket_count(other.bucket_count),
		buckets(other.bucket_count, nullptr)
	{
		for (size_t i = 0; i < other.buckets.size_(); i++)
		{
			Node<K, V>* other_current = other.buckets[i];
			Node<K, V>* last_created = nullptr;

			while (other_current != nullptr)
			{
				Node<K, V>* newNode = allocator.allocate(1);
				new (newNode) Node<K, V>{other_current->key, other_current->value, nullptr};

				if (last_created == nullptr)
					buckets[i] = newNode;
				else
					last_created->next = newNode;

				last_created = newNode;
				other_current = other_current->next;
			}
		}
	}

	MyUnorderedMap(MyUnorderedMap&& other) :
		bucket_count(other.bucket_count),
		buckets(std::move(other.buckets))
	{
		other.bucket_count = 0;
	}

	MyUnorderedMap& operator=(const MyUnorderedMap& other)
	{
		if (this == &other) return *this;

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

		bucket_count = other.bucket_count;
		buckets = vector_l<Node<K, V>*>(other.bucket_count, nullptr);

		for (size_t i = 0; i < other.buckets.size_(); i++)
		{
			Node<K, V>* other_current = other.buckets[i];
			Node<K, V>* last_created = nullptr;

			while (other_current != nullptr)
			{
				Node<K, V>* newNode = allocator.allocate(1);
				new (newNode) Node<K, V>{other_current->key, other_current->value, nullptr};

				if (last_created == nullptr)
					buckets[i] = newNode;
				else
					last_created->next = newNode;

				last_created = newNode;
				other_current = other_current->next;
			}
		}
		
		return *this;
	}

	MyUnorderedMap& operator=(MyUnorderedMap&& other)
	{
		if (this == &other) return *this;

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

		bucket_count = other.bucket_count;
		buckets = std::move(other.buckets);

		other.bucket_count = 0;

		return *this;
	}

	void erase(const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];
		Node<K, V>* previous = buckets[index];
		
		while (current != nullptr)
		{
			if (current->key == key)
			{
				if (current->next != nullptr)
					previous->next = current->next;
				else if (previous != current)
					previous->next = nullptr;

				current->~Node();
				allocator.deallocate(current, 1);
				return;
			}

			previous = current;
			current = current->next;
		}

	}
};



int main()
{

	MyUnorderedMap<std::string, int> map;
	map.TempAdd(new Node<std::string, int>(std::string("test"), 5, nullptr));
	int test = map["test"];
	std::cout << test << std::endl;

	MyUnorderedMap<std::string, int> map2 = map;
	std::string truc = "truc";
	map2.insert(truc, 8);
	//map2["truc"] = 34;
	int test2 = map2["truc"];
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