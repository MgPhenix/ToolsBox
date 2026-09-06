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

	using iterator = T*;
	using const_iterator = const T*;

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

	size_t capacity_() const { return capacity; };
	size_t size_()	   const { return size; };

	iterator begin() const { return memory; };
	iterator end()	 const { return memory + size; };

	iterator erase(size_t indice)
	{
		if (indice >= size)
			return memory;

		T* new_memory = allocator.allocate(capacity);

		size_t i = 0;
		size_t j = 0;
		while (i < size)
		{
			if (i == indice)
				i++;

			new (&new_memory[j]) T(std::move_if_noexcept(memory[i]));
			memory[i].~T();

			i++;
			j++;
		}

		allocator.deallocate(memory, capacity);
		memory = new_memory;
		size--;
		return memory;
	}

	iterator erase(iterator it)
	{
		if (it == end())
			return memory;


		T* new_memory = allocator.allocate(capacity);

		size_t i = 0;
		size_t j = 0;
		while (i < size)
		{
			if (&memory[i] == it)
				i++;

			new (&new_memory[j]) T(std::move_if_noexcept(memory[i]));
			memory[i].~T();

			i++;
			j++;
		}

		allocator.deallocate(memory, capacity);
		memory = new_memory;
		size--;
		return memory;
	}

	void erase_if(std::function<bool(const T&)> func)
	{
		T* new_memory = allocator.allocate(capacity);

		size_t i = 0;
		size_t j = 0;
		size_t count = 0;
		while (i < size)
		{
			if (func(memory[i]))
			{
				memory[i].~T();
				count++;
			}
			else
			{
				new (&new_memory[j]) T(std::move_if_noexcept(memory[i]));
				memory[i].~T();
				j++;
			}

			i++;
		}

		allocator.deallocate(memory, capacity);
		memory = new_memory;
		size -= count;
		return;
	}

	void erase_move_if(std::function<bool(const T&)> func)
	{
		size_t i = 0;
		size_t count = 0;
		while (i < size)
		{
			if (func(memory[i]))
			{
				memory[i].~T();
				if(i != size-1)
					new (&memory[i]) T(std::move_if_noexcept(memory[i + 1]));
				count++;
			}

			i++;
		}

		size -= count;
		return;
	}

	void erase_move(size_t indice)
	{
		if (indice >= size)
			return;

		size_t i = 0;
		while (i < size)
		{	
			if (i == indice)
				memory[i].~T();			
			else if (i > indice)
				new (&memory[i-1]) T(std::move_if_noexcept(memory[i]));

			i++;
		}
		
		size--;
	}

	void erase_move(iterator it)
	{
		if (it == end())
			return;

		size_t i = 0;
		bool passedBy = false;
		while (i < size)
		{
			if (it == &memory[i])
			{ 	
				memory[i].~T();
				passedBy = true;
			}
			else if (passedBy)
				new (&memory[i - 1]) T(std::move_if_noexcept(memory[i]));

			i++;
		}

		size--;
	}

	T& operator[](size_t position) const
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