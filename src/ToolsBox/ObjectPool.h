#pragma once
#include "PrimitiveTypes.h"
#include <vector>


template<typename T>
class ObjectPool
{
private:

	std::vector<T> m_objectPool;
	std::vector<bool> m_active;

public:

	ObjectPool(size_t size) :
		m_objectPool(size),
		m_active(size, false) { }

	T* GetInactiveObject()
	{
		for (size_t i = 0; i < m_objectPool.size(); i++)
		{
			if (!m_active[i])
			{
				m_active[i] = true;
				return &m_objectPool[i];
			}
		}
		return nullptr;
	}

	std::vector<T*> GetInactivesObjects(int32 nbr)
	{
		std::vector<T*> result;

		for (int32 i = 0; i < nbr; i++)
		{
			T* object = GetInactiveObject();
			if (!object)
				continue;

			result.push_back(object);
		}

		return result;
	}

	void ReleaseObject(T* object)
	{
		size_t index = object - &m_objectPool[0];
		
		if (index > m_objectPool.size() || index < 0)
			return;
	
		m_active[index] = false;
	}
};

