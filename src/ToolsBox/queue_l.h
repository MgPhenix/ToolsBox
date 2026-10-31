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

#if defined(LINUX) || defined(MACOS)
#include <cstddef>
#endif



template<typename T>
struct QueueNode
{
	T value;
	QueueNode<T>* next = nullptr;
};

template<typename T>
class queue_l
{
private:

	QueueNode<T>* first = nullptr;
	size_t size = 0;
	
private:

	QueueNode<T>* FrontNode()
	{
		return first;
	}

	QueueNode<T>* BackNode()
	{
		if (first == nullptr)
			return nullptr;

		QueueNode<T>* current = first;
		while (current->next != nullptr)
			current = current->next;

		return current;
	}

	QueueNode<T>* PreviousBackNode()
	{
		if (first == nullptr)
			return nullptr;

		QueueNode<T>* current = first;
		for (size_t i = 0; i < size - 1; i++)
			current = current->next;

		return current;
	}

public:

	queue_l() = default;

	size_t Size() { return size; };

	T& Front() { return FrontNode()->value; };
	T& Back() { return BackNode()->value; };

	void push(T&& value)
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

	T& operator[](size_t indice)
	{
		if (indice >= size) 
			throw;

		QueueNode<T>* current = first;
		for(size_t i = 0; i < indice; i++)
			current = current->next;


		return current->value;
	}

	T pop()
	{
		if (first == nullptr) 
			throw;

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

	T pop_back()
	{
		if (first == nullptr)
			throw;

		QueueNode<T>* previous_back = PreviousBackNode();
		QueueNode<T>* back = previous_back->next;

		T value = back->value;

		previous_back->next = nullptr;
		delete back;

		return value;
	}
};