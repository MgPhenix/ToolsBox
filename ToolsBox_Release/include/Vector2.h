#pragma once
#include <math.h>

template<typename T>
class Vector2
{
public:

	T x;
	T y;

	Vector2() :
		x(0),
		y(0)
	{};

	Vector2(T _x, T _y) :
		x(_x),
		y(_y)
	{};

	Vector2(Vector2& vector2) :
		x(vector2.x),
		y(vector2.y)
	{};

	Vector2<T>& operator+=(const Vector2<T> & other)
	{
		x += other.x;
		y += other.y;
		return *this;
	};

	Vector2<T>& operator-=(const Vector2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	};

	Vector2<T>& operator*=(const Vector2<T>& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	};

	Vector2<T>& operator*=(const T other)
	{
		x *= other;
		y *= other;
		return *this;
	};

	Vector2<T>& operator/=(const Vector2<T>& other)
	{
		if (other.x == 0 || other.y == 0) 
			return *this;

		x /= other.x;
		y /= other.y;
		return *this;
	};

	Vector2<T>& operator/=(const T other)
	{
		if (other == 0)
			return *this;

		x /= other;
		y /= other;
		return *this;
	};

	Vector2<T> operator+(const Vector2<T>& other) const
	{
		return Vector2<T>(x + other.x, y + other.y); 
	};

	Vector2<T> operator-(const Vector2<T>& other) const
	{
		return Vector2<T>(x - other.x, y - other.y);
	};

	Vector2<T> operator*(const Vector2<T>& other) const
	{
		return Vector2<T>(x * other.x, y * other.y);
	};

	Vector2<T> operator*(const T other) const
	{
		return Vector2<T>(x * other, y * other);
	};

	Vector2<T> operator/(const Vector2<T>& other) const
	{
		if (other.x == 0 || other.y == 0) 
			return *this;
		return Vector2<T>(x / other.x, y / other.y);
	};

	Vector2<T> operator/(const T other) const
	{
		if (other == 0) 
			return *this;
		return Vector2<T>(x / other, y / other);
	};


	bool operator==(const Vector2<T>& other) const
	{
		return x == other.x && y == other.y;
	};

	T Length()
	{
		return sqrt(LengthSqr());
	};

	T LengthSqr()
	{
		return x * x + y * y;
	};


	Vector2<T> Normalized()
	{
		T len = Length();
		if (len > 0)
			return *this / len;
		return Vector2<T>();
	}

	void Normalize()
	{
		T len = Length();
		if (len > 0)
			return;
		x /= len;
		y /= len;
	}

	T Distance(const Vector2<T>& other) const
	{
		T dx = x - other.x;
		T dy = y - other.y;

		return sqrt(dx * dx + dy * dy);
	};

	T Dot(const Vector2<T>& other) const
	{
		return x * other.x + y + other.y;
	}
};