/**
* @file SharedPtr.h
* @brief 
*
* @version 0.1
* @date 2026-07-04
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "PrimitiveTypes.h"

template<typename T>
class SharedPtr
{
private:

	T* ptr;
	int32* refcount;

	void Release()
	{
		if (!refcount) return;

		(*refcount)--;
		if (*refcount == 0)
		{
			delete ptr;
			delete refcount;
		}
	};

public:

	explicit SharedPtr(T* newPtr = nullptr) :
		ptr(newPtr),
		refcount(new int32(ptr ? 1 : 0))
	{
	};

	SharedPtr(const SharedPtr& other) :
		ptr(other.ptr),
		refcount(other.refcount)
	{
		if (refcount) (*refcount)++;
	};

	SharedPtr(SharedPtr&& other) :
		ptr(other.ptr),
		refcount(other.refcount)
	{
		other.ptr = nullptr;
		other.refcount = nullptr;
	};

	~SharedPtr() { Release(); };


	SharedPtr& operator=(const SharedPtr& other)
	{
		if (this == &other) return *this;

		Release();
		ptr = other.ptr;
		refcount = other.refcount;

		if (refcount)
			(*refcount)++;

		return *this;
	};

	int32 GetCount() { return refcount ? *refcount : 0; };

	T* operator->() const {
		return ptr;
	};

	T& operator*() const {
		return *ptr;
	};
};