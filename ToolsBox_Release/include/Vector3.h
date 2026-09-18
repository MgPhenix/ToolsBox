/**
* @file Vector3.h
* @brief
*
* @version 0.1
* @date 2026-09-18
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once

/**
* @brief A simple template 3d Vector
*/
template<typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	Vector3() :
		x(0),
		y(0),
		z(0)
	{};

	Vector3(T _x, T _y, T _z) :
		x(_x),
		y(_y),
		z(_z)
	{};

	Vector3(const Vector3& Vector3) :
		x(Vector3.x),
		y(Vector3.y),
		z(Vector3.z)
	{};

	Vector3<T>& operator+=(const Vector3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	};

	Vector3<T>& operator-=(const Vector3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	};

	Vector3<T>& operator*=(const Vector3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	};

	Vector3<T>& operator*=(const T other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	};

	Vector3<T>& operator/=(const Vector3<T>& other)
	{
		if (other.x == 0 || other.y == 0 || other.z == 0)
			return *this;

		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	};

	Vector3<T>& operator/=(const T other)
	{
		if (other == 0)
			return *this;

		x /= other;
		y /= other;
		z /= other;
		return *this;
	};

	Vector3<T> operator+(const Vector3<T>& other) const
	{
		return Vector3<T>(x + other.x, y + other.y, z + other.z);
	};

	Vector3<T> operator-(const Vector3<T>& other) const
	{
		return Vector3<T>(x - other.x, y - other.y, z - other.z);
	};

	Vector3<T> operator*(const Vector3<T>& other) const
	{
		return Vector3<T>(x * other.x, y * other.y, z * other.z);
	};

	Vector3<T> operator*(const T other) const
	{
		return Vector3<T>(x * other, y * other, z * other);
	};

	Vector3<T> operator/(const Vector3<T>& other) const
	{
		if (other.x == 0 || other.y == 0 || other.z == 0)
			return *this;
		return Vector3<T>(x / other.x, y / other.y, z / other.z);
	};

	Vector3<T> operator/(const T other) const
	{
		if (other == 0)
			return *this;
		return Vector3<T>(x / other, y / other, z / other);
	};

	bool operator==(const Vector3<T>& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	};

	T Length()
	{
		return sqrt(LengthSqr());
	};

	T LengthSqr()
	{
		return x * x + y * y + z * z;
	};

	Vector3<T> Normalized()
	{
		T len = Length();
		if (len > 0)
			return *this / len;
		return Vector3<T>();
	}

	void Normalize()
	{
		T len = Length();
		if (len > 0)
			return;
		x /= len;
		y /= len;
		z /= len;
	}

	T Distance(const Vector3<T>& other) const
	{
		T dx = x - other.x;
		T dy = y - other.y;
		T dz = z - other.z;

		return sqrt(dx * dx + dy * dy + dz * dz);
	};

	T Dot(const Vector3<T>& other) const
	{
		return x * other.x + y + other.y + z * other.z;
	}
};