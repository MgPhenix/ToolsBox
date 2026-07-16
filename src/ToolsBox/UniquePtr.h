#pragma once
#include "SmartPtrBase.h"

template<typename T>
class UniquePtr : public SmartPtrBase<T>
{
public:

	UniquePtr(T* newPtr = nullptr) :
		ptr(newPtr)
	{}
	
	UniquePtr(UniquePtr&& other) :
		ptr(other.ptr)
	{
		other.ptr = nullptr;
	}
	
	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;

	~UniquePtr() { delete ptr; };

	UniquePtr& operator=(UniquePtr&& other)
	{
		if (this == other) return *this;

		ptr(other);
		other.ptr = nullptr;
		return *this;
	}
};