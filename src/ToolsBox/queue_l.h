#pragma once

template<typename T>
struct Node
{
	T value;
	Node<T>* next = nullptr;
};

template<typename T>
class queue_l
{
private:

	Node<T>* first = nullptr;
	size_t size = 0;
	
public:

	queue_l() = default;

	size_t Size() { return size; };

	void push(T&& value)
	{
		size++;

		if (first == nullptr)
		{
			first = new Node<T>;
			first->value = value;
			return;
		}

		Node<T>* current = first;

		while (current->next != nullptr)
		{
			current = current->next;
		}

		Node<T>* new_node = new Node<T>;
		new_node->value = value;
		current->next = new_node;
	}

	T& operator[](size_t indice)
	{
		if (indice >= size) 
			throw;

		Node<T>* current = first;
		for(size_t i = 0; i <= indice; i++)
			current = current->next;


		return current->value;
	}

	T& pop()
	{
		if (first == nullptr) 
			throw;

		T& value = first->value;

		if (first->next == nullptr)
		{
			delete first;
			first = nullptr;
			size--;
		}
		else
		{
			Node<T*> old_first = first;
			first = first->next;
			delete old_first;
			size--;
		}

		return value;
	}
};