#pragma once

template<typename T>
class SmartPtrBase
{
protected:

	T* ptr;

public:

	T* operator->() const {
		return ptr;
	};

	T& operator*() const {
		return *ptr;
	};
};