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