/**
* @file unordered_map_l.h
* @brief Light version of std::unordered_map (still WIP)
*
* @version 1.0
* @date 2026-09-16
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once


#include "allocator_l.h"
#include "Pair.h"
#include "vector_l.h"
#include <iostream>

/**
* @brief Just a Node struct, only mean to be used by unordered_map_l
*/
template<typename K, typename V>
struct Node
{
	K key;
	V value;
	Node* next;

	Node(K k, V v, Node* node) :
		key(k),
		value(v),
		next(node) {}

	Node(const Node& other) :
		key(other.key),
		value(other.value),
		next(other.next)
	{}

	Node(Node&& other) :
		key(other.key),
		value(other.value),
		next(other.next)
	{
		other.next = nullptr;
	}
};

/**
* @brief Custom unordered map still W.I.P do not use for now
*/
template<typename K, typename V, typename Allocator = MyAllocator<Node<K, V>>>
class unordered_map_l
{
private:

	vector_l<Node<K, V>*> buckets;
	Allocator			  allocator;
	size_t				  bucket_count = 8;

public:

	unordered_map_l() : buckets(8, nullptr) {}

	~unordered_map_l()
	{
		for (auto& bucket : buckets)
		{
			Node<K, V>* current = bucket;
			while (current != nullptr)
			{
				Node<K, V>* next = current->next;

				current->~Node();
				allocator.deallocate(current, 1);
				current = next;
			}
		}
	}
	/**
	* @return If key is valid return the pointer attached to the key
	*/
	V* find(const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
				return &current->value;
			current = current->next;
		}

		return nullptr;
	}
	/**
	* @brief Add a pair Key, Value in the map
	*/
	void insert(K key, V value)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		if (current != nullptr)
		{
			while (current->next != nullptr)
			{
				if (current->next->key == key)
					return;
				current = current->next;
			}
		}

		Node<K, V>* newNode = allocator.allocate(1);
		new (newNode) Node<K, V>(std::move_if_noexcept(key), std::move_if_noexcept(value), nullptr);

		if (current == nullptr)
			buckets[index] = newNode;
		else
			current->next = newNode;
	}

	bool contains(const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
				return true;
			current = current->next;
		}

		return false;
	}

	V& operator[](const K& key)
	{
		V* value = find(key);
		if (value != nullptr)
			return *value;

		insert(key, V());
		return *find(key);
	}

	void clear()
	{
		for (auto& bucket : buckets)
		{
			Node<K, V>* current = bucket;
			while (current != nullptr)
			{
				Node<K, V>* next = current->next;

				current->~Node();
				allocator.deallocate(current, 1);
				current = next;
			}
		}
	}

	unordered_map_l(const unordered_map_l& other) :
		bucket_count(other.bucket_count),
		buckets(other.bucket_count, nullptr)
	{
		for (size_t i = 0; i < other.buckets.size_(); i++)
		{
			Node<K, V>* other_current = other.buckets[i];
			Node<K, V>* last_created = nullptr;

			while (other_current != nullptr)
			{
				Node<K, V>* newNode = allocator.allocate(1);
				new (newNode) Node<K, V>{other_current->key, other_current->value, nullptr};

				if (last_created == nullptr)
					buckets[i] = newNode;
				else
					last_created->next = newNode;

				last_created = newNode;
				other_current = other_current->next;
			}
		}
	}

	unordered_map_l(unordered_map_l&& other) :
		bucket_count(other.bucket_count),
		buckets(std::move(other.buckets))
	{
		other.bucket_count = 0;
	}

	unordered_map_l& operator=(const unordered_map_l& other)
	{
		if (this == &other) return *this;

		for (auto& bucket : buckets)
		{
			Node<K, V>* current = bucket;
			while (current != nullptr)
			{
				Node<K, V>* next = current->next;

				current->~Node();
				allocator.deallocate(current, 1);
				current = next;
			}
		}

		bucket_count = other.bucket_count;
		buckets = vector_l<Node<K, V>*>(other.bucket_count, nullptr);

		for (size_t i = 0; i < other.buckets.size_(); i++)
		{
			Node<K, V>* other_current = other.buckets[i];
			Node<K, V>* last_created = nullptr;

			while (other_current != nullptr)
			{
				Node<K, V>* newNode = allocator.allocate(1);
				new (newNode) Node<K, V>{other_current->key, other_current->value, nullptr};

				if (last_created == nullptr)
					buckets[i] = newNode;
				else
					last_created->next = newNode;

				last_created = newNode;
				other_current = other_current->next;
			}
		}

		return *this;
	}

	unordered_map_l& operator=(unordered_map_l&& other)
	{
		if (this == &other) return *this;

		for (auto& bucket : buckets)
		{
			Node<K, V>* current = bucket;
			while (current != nullptr)
			{
				Node<K, V>* next = current->next;

				current->~Node();
				allocator.deallocate(current, 1);
				current = next;
			}
		}

		bucket_count = other.bucket_count;
		buckets = std::move(other.buckets);

		other.bucket_count = 0;

		return *this;
	}
	/**
	* @brief Erase a value attached to the key
	*/
	void erase(const K& key)
	{
		size_t index = std::hash<K>{}(key) % bucket_count;
		Node<K, V>* current = buckets[index];
		Node<K, V>* previous = buckets[index];

		while (current != nullptr)
		{
			if (current->key == key)
			{
				if (current->next != nullptr)
					previous->next = current->next;
				else if (previous != current)
					previous->next = nullptr;

				current->~Node();
				allocator.deallocate(current, 1);
				return;
			}

			previous = current;
			current = current->next;
		}

	}
};