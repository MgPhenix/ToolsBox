/**
* @file allocator_l.h
* @brief idk for now
*
* @version 0.1
* @date 2026-07-30
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once

/**
* @brief A really simple memory Allocator
*/
template<typename T>
struct MyAllocator
{
	using value_type = T;

	MyAllocator() = default;

	/**
	* @brief Allocate a zone of memory
	* @param size_t size : Size of memory you want to allocate, memory allocated will be sizeof(T) * size
	* @return T* : A pointer to the allocated memory address
	*/
	T* allocate(size_t size)
	{
		return static_cast<T*>(::operator new(size * sizeof(T)));
	}

	/**
	* @brief Deallocate a zone of memory
	* @param T* ptr : A pointer to an allocated memory adress
	* @param size_t size : Size of memory you want to deallocate, memory deallocated will be sizeof(T) * size
	*/
	void deallocate(T* ptr, size_t size)
	{
		::operator delete(ptr, size * sizeof(T));
	}

	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};
};