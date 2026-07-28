#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

template<typename T>
struct MyAllocator
{
	using value_type = T;

	MyAllocator() = default;

	T* allocate(size_t size)
	{
		std::cout << "Allocate(" << size << ")" << std::endl;
		return static_cast<T*>(::operator new(size * sizeof(T)));
	}

	void deallocate(T* ptr, size_t size)
	{
		std::cout << "Deallocate(" << size << ")" << std::endl;
		::operator delete(ptr, size * sizeof(T));
	}

	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};
};

template<typename T, typename Allocator = MyAllocator<T>>
class MyVector
{
private:

	Allocator allocator;
	T* memory;

	size_t size		= 0;
	size_t capacity = 1;

public:

	MyVector()
	{
		memory = allocator.allocate(1);
	}

	void push_back(T&& val)
	{
		if (size == capacity)
		{
			T* new_memory = allocator.allocate(capacity * 2);
			for (size_t i = 0; i < size; i++)
			{
				new (&new_memory[i]) T(std::move_if_noexcept(memory[i]));
				memory[i].~T();
			}

			allocator.deallocate(memory, capacity);
			memory = new_memory;
			capacity *= 2;
		}

		new (&memory[size]) T(std::move_if_noexcept(val));
		size++;
	};

	size_t capacity_()  { return capacity; };
	size_t size_()		{ return size; };

	T& operator[](size_t position)
	{
		ASSERT(position <= size);

		return memory[position];
	}

	~MyVector()
	{
		for (size_t i = 0; i < size; i++)
			memory[i].~T();

		allocator.deallocate(memory, capacity);
	}
};

struct Test
{
	int x = 42;
	Test() { std::cout << "Test constructor" << std::endl; };
	Test(const Test&) { std::cout << "Test copie" << std::endl; };
	Test(Test&&) noexcept { std::cout << "Test move" << std::endl; };
	~Test() { std::cout << "Test destructor" << std::endl; };
};

struct Node { int key; float value; };

int main()
{
	MyAllocator<float> alloc;

	using ReboundAllocType = MyAllocator<float>::rebind<Node>::other;
	ReboundAllocType allocNode;

	Node* n = allocNode.allocate(1);
	new (n) Node{ 42, 3.14f };

	std::cout << "Key : " << n->key << " | Value : " << n->value << std::endl;
	n->~Node();
	allocNode.deallocate(n, 1);
	return 0;
}



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