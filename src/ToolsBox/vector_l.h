/**
* @file vector_l.h
* @brief idk for now
*
* @version 0.1
* @date 2026-07-30
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "allocator_l.h"

#define ASSERT( condition ) if ( condition == false ) throw; // scotch solution

/**
* @brief vector light
*/
template<typename T, typename Allocator = MyAllocator<T>>
class vector_l
{
private:

	Allocator allocator;
	T* memory;

	size_t size = 0;
	size_t capacity = 1;

public:

	vector_l()
	{
		memory = allocator.allocate(1);
	}

	vector_l(size_t _size, T* value) :
		size(_size),
		capacity(_size)
	{
		memory = allocator.allocate(capacity);
		for (size_t i = 0; i < size; i++)
			new (&memory[i]) T*(value);
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

	template<typename... Args>
	void emplace_back(Args&&... args)
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

		new (&memory[size]) T(std::forward<Args>(args)...);
		size++;
	}

	void pop_back()
	{
		ASSERT(size != 0);
		memory[size - 1].~T();
		size--;
	}

	size_t capacity_() { return capacity; };
	size_t size_() { return size; };

	T* begin() { return memory; };
	T* end() { return memory + size; };

	T& operator[](size_t position)
	{
		ASSERT(position < size);

		return memory[position];
	}

	~vector_l()
	{
		for (size_t i = 0; i < size; i++)
			memory[i].~T();

		allocator.deallocate(memory, capacity);
	}

	vector_l(const vector_l& other) :
		allocator(other.allocator),
		capacity(other.capacity),
		size(other.size)
	{
		memory = allocator.allocate(capacity);
		for (size_t i = 0; i < other.size; i++)
			new (&memory[i]) T(other.memory[i]);
	}

	vector_l(vector_l&& other) :
		allocator(other.allocator),
		capacity(other.capacity),
		memory(other.memory),
		size(other.size)
	{
		other.memory = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

	vector_l& operator=(vector_l&& other)
	{
		if (this == &other) return *this;

		for (size_t i = 0; i < size; i++)
			memory[i].~T();

		allocator.deallocate(memory, capacity);

		capacity = other.capacity;
		size = other.size;

		memory = other.memory;

		other.memory = nullptr;
		other.capacity = 0;
		other.size = 0;

		return *this;
	}

	vector_l& operator=(const vector_l& other)
	{
		if (this == &other) return *this;

		for (size_t i = 0; i < size; i++)
			memory[i].~T();

		allocator.deallocate(memory, capacity);

		capacity = other.capacity;
		size = other.size;

		memory = allocator.allocate(capacity);
		for (size_t i = 0; i < size; i++)
			new (&memory[i]) T(other.memory[i]);

		return *this;
	}
};