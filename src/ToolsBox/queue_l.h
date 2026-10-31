/**
* @file queue_l.h
* @brief A simple queue (W.I.P)
*
* @version 1.1
* @date 2026-10-30
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix) & Marien-Garon (https://github.com/Marien-Garon)
*/
#pragma once
#include "Config.h"
#include <stdexcept>

#if defined(LINUX) || defined(MACOS)
#include <cstddef>
#endif


/**
* @brief Simple queue node who store the T value and a pointer to the next node
*/
template<typename T>
struct QueueNode
{
	T value;
	QueueNode<T>* next = nullptr;
};

/**
* @brief A Queue designed to be light and usefull with multiple function
*/
template<typename T>
class queue_l
{
private:

	QueueNode<T>* first = nullptr;
	size_t size = 0;
	
private:

	QueueNode<T>* FrontNode() const
	{
		return first;
	}

	QueueNode<T>* BackNode() const
	{
		if (first == nullptr)
			return nullptr;

		QueueNode<T>* current = first;
		while (current->next != nullptr)
			current = current->next;

		return current;
	}

	QueueNode<T>* PreviousBackNode() const
	{
		if (first == nullptr)
			return nullptr;

		QueueNode<T>* current = first;
		for (size_t i = 0; i < size - 1; i++)
			current = current->next;

		return current;
	}

public:

	/**
	* @brief Default constructor
	*/
	queue_l() = default;
	/**
	* @return Return the size_t size of the queue
	*/
	size_t Size() const { return size; };
	/**
	* @return Return the first value of the queue
	*/
	T& Front() const { return FrontNode()->value; };
	/**
	* @return Return the last value of the queue
	*/
	T& Back()  const { return BackNode()->value;  };

public:

	/**
	* @brief Insert a value in the back of the queue
	* @tparam T value : Value you want to insert
	*/
	void push(T& value)
	{
		size++;

		if (first == nullptr)
		{
			first = new QueueNode<T>;
			first->value = value;
			return;
		}

		QueueNode<T>* back = BackNode();

		QueueNode<T>* new_node = new QueueNode<T>;
		new_node->value = value;
		back->next = new_node;
	}
	/**
	* @brief Detach the first element from the queue and return it
	* @return Return the first T value of the queue
	*/
	T pop()
	{
		if (first == nullptr)
			throw std::runtime_error("queue_l : queue is empty");

		T value = first->value;

		if (first->next == nullptr)
		{
			delete first;
			first = nullptr;
			size--;
		}
		else
		{
			QueueNode<T>* old_first = first;
			first = first->next;
			delete old_first;
			size--;
		}

		return value;
	}
	/**
	* @brief Detach the last element from the queue and return it
	* @return Return the last T value of the queue
	*/
	T pop_back()
	{
		if (first == nullptr)
			throw std::runtime_error("queue_l : queue is empty");

		QueueNode<T>* previous_back = PreviousBackNode();
		QueueNode<T>* back = previous_back->next;

		T value = back->value;

		previous_back->next = nullptr;
		delete back;

		return value;
	}

	T& operator[](size_t indice) const
	{
		if (indice >= size) 
			throw std::out_of_range("queue_l : index out of range");

		QueueNode<T>* current = first;
		for(size_t i = 0; i < indice; i++)
			current = current->next;


		return current->value;
	}
};