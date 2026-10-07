/**
* @file Collider.h
* @brief Bunch of collider like AABB, OOBB and more 
*
* @version 1.1
* @date 2026-09-30
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include "Vector2.h"

enum class CollisionDirection
{
	UP,
	DOWN,
	RIGHT,
	LEFT,

	NONE
};

struct RecCollider
{
	int x	   = 0;
	int y	   = 0;
	int width  = 0;
	int height = 0;
	
	RecCollider() = default;

	RecCollider(int px, int py, int w, int h) :
		x(px),
		y(py),
		width(w),
		height(h)
	{ }

	RecCollider(const RecCollider& other) :
		x(other.x),
		y(other.y),
		width(other.width),
		height(other.height)
	{ }
};

struct CircleCollider
{
	int x = 0;
	int y = 0;
	int radius = 0;

	CircleCollider(int px, int py, int r) :
		x(px),
		y(py),
		radius(r)
	{ }

	bool IsColliding(const CircleCollider& other)
	{
		int d2 = (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
		if (d2 > (radius + other.radius) * (radius + other.radius))
			return false;
		return true;
	}

	template<typename T>
	bool IsCollidingWith(Vector2<T> pos)
	{
		int d2 = (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y);
		if (d2 > radius * radius)
			return false;
		return true;
	}
};

struct AABBCollider : public RecCollider
{
	AABBCollider(int px, int py, int w, int h) : RecCollider(px, py, w, h) {};

	bool IsCollidingWith(const AABBCollider& other) const
	{
		return (other.x >= x + width)      // droite
			|| (other.x + other.width <= x) // gauche
			|| (other.y >= y + height) // bas
			|| (other.y + other.height <= y);  // haut
	}
	
	template<typename T>
	bool IsCollidingWith(Vector2<T> pos) const
	{
		return pos.x >= x && pos.x < x + width && pos.y >= y && pos.y < y + height;
	}
};


bool Colliding(const AABBCollider& collider_a, const AABBCollider& collider_b)
{
	return collider_a.IsCollidingWith(collider_b);
}
