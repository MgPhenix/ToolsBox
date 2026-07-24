#pragma once
#include "PrimitiveTypes.h"
#include <vector>


/**
* @brief Create a pool of T object that you can use whenever you want
* @brief Never delete a pointer that the pool give you
*/
template<typename T>
class ObjectPool
{
private:

	std::vector<T>	  m_objectPool;
	std::vector<bool> m_active;

public:

	explicit ObjectPool(size_t size) :
		m_objectPool(size),
		m_active(size, false) { }

	/**
	* @brief Get an inactive object from the pool
	* @return T* Object that you can use, never delete it or you will break the pool
	*/
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

	/**
	* @brief Get a list of inactive object from the pool
	* @return vector of T* Object that you can use, never delete any of them or you will break the pool
	*/
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

	/**
	* @brief Release an object that you don't need anymore
	* @brief Don't forget to release object or you will not have inactive object anymore
	*/
	void ReleaseObject(T* object)
	{
		size_t index = object - &m_objectPool[0];
		
		if (index > m_objectPool.size() || index < 0)
			return;
	
		m_active[index] = false;
	}
};