#pragma once
#include "PrimitiveTypes.h"
#include "SmartPtrBase.h"

template<typename T>
class SharedPtr : public SmartPtrBase<T>
{
private:

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

	SharedPtr(T* newPtr = nullptr) :
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
		if (this == other) return *this;

		Release();
		ptr = other.ptr;
		refcount = other.refcount;

		if (refcount)
			(*refcount)++;

		return *this;
	};

	int32 GetCount() { return refcount ? *refcount : 0; };
};