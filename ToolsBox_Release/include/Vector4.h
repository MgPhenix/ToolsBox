/**
* @file Vector4.h
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
* @brief A simple template 4d Vector
*/
template<typename T>
struct Vector4
{
	T x;
	T y;
	T z;
	T w;

	Vector4() :
		x(0),
		y(0),
		z(0),
		w(0)
	{};

	Vector4(T _x, T _y, T _z, T _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{};

	Vector4(const Vector4& Vector4) :
		x(Vector4.x),
		y(Vector4.y),
		z(Vector4.z),
		w(Vector4.w)
	{};

	Vector4<T>& operator+=(const Vector4<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	};

	Vector4<T>& operator-=(const Vector4<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	};

	Vector4<T>& operator*=(const Vector4<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	};

	Vector4<T>& operator*=(const T other)
	{
		x *= other;
		y *= other;
		z *= other;
		w *= other;
		return *this;
	};

	Vector4<T>& operator/=(const Vector4<T>& other)
	{
		if (other.x == 0 || other.y == 0 || other.z == 0 || other.w == 0)
			return *this;

		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	};

	Vector4<T>& operator/=(const T other)
	{
		if (other == 0)
			return *this;

		x /= other;
		y /= other;
		z /= other;
		w /= other;
		return *this;
	};

	Vector4<T> operator+(const Vector4<T>& other) const
	{
		return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
	};

	Vector4<T> operator-(const Vector4<T>& other) const
	{
		return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
	};

	Vector4<T> operator*(const Vector4<T>& other) const
	{
		return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
	};

	Vector4<T> operator*(const T other) const
	{
		return Vector4<T>(x * other, y * other, z * other, w * other);
	};

	Vector4<T> operator/(const Vector4<T>& other) const
	{
		if (other.x == 0 || other.y == 0 || other.z == 0 || other.w == 0)
			return *this;
		return Vector4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
	};

	Vector4<T> operator/(const T other) const
	{
		if (other == 0)
			return *this;
		return Vector4<T>(x / other, y / other, z / other, w / other);
	};

	bool operator==(const Vector4<T>& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	};
};