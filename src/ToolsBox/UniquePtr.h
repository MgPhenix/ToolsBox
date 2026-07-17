#pragma once

template<typename T>
class UniquePtr
{
private:

	T* ptr;

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
		if (this == &other) return *this;

		ptr(other);
		other.ptr = nullptr;
		return *this;
	};

	T* operator->() const {
		return ptr;
	};

	T& operator*() const {
		return *ptr;
	};
};