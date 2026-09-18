/**
* @file Matrice.h
* @brief A Generic Matrice class :/
*
* @version 0.1
* @date 2026-09-18
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once


#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Pair.h"
#include "Traits.h"


#pragma region Matrice

template<int columns, int rows, typename T>
class Matrice
{
public:

	T m_value[columns * rows];

	int m_size = 0;

public:

	int GetIndice(int column, int row) const 
	{ 
		return row * columns + column; 
	};

	T* GetData() { return m_value; };

	T& GetValue(int column, int row)
	{
		ASSERT((column > columns - 1 || column < 0 || row < 0 || row > rows - 1) == false);

		return m_value[GetIndice(column, row)];
	};

	void SetValue(int column, int row, T value)
	{
		ASSERT((column > columns - 1 || column < 0 || row < 0 || row > rows - 1) == false);

		m_value[GetIndice(column, row)] = value;
	}

	Pair<int, int> GetColumnAndRow() { return { columns, rows }; };

	int GetSize() { return m_size; };

	Matrice() :
		m_size(columns* rows)
	{
		for (int i = 0; i < m_size; i++)
			m_value[i] = 0;
	}

	Matrice(T* value) :
		m_size(columns* rows)
	{
		for (int i = 0; i < m_size; i++)
			m_value[i] = value[i];
	}

	T& operator()(int column, int row)
	{
		return GetValue(column, row);
	}

	Matrice operator+(const Matrice& other)
	{
		Matrice<columns, rows, T> new_matrice;

		for (int i = 0; i < m_size; i++)
			new_matrice.m_value[i] = m_value[i] + other.m_value[i];
		return new_matrice;
	}

	Matrice& operator+=(const Matrice& other)
	{
		for (int i = 0; i < m_size; i++)
			m_value[i] += other.m_value[i];
		return *this;
	}

	template<Number Nbr>
	Matrice& operator*=(const Nbr& scalar)
	{
		for (int i = 0; i < m_size; i++)
			m_value[i] *= scalar;
		return *this;
	}

	template<Number Nbr>
	Matrice& operator*(const Nbr& scalar)
	{
		Matrice<columns, rows, T> new_matrice;

		for (int i = 0; i < m_size; i++)
			new_matrice.m_value[i] = m_value[i] * scalar;
		return new_matrice;
	}

	template<int other_columns>
	Matrice<other_columns, rows, T> operator*(const Matrice<other_columns, columns, T>& other)
	{
		Matrice<other_columns, rows, T> new_matrice;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < other_columns; j++)
			{
				T value = 0;
				for (int k = 0; k < columns; k++)
					value += m_value[GetIndice(k, i)] * other.m_value[other.GetIndice(j, k)];

				new_matrice.m_value[new_matrice.GetIndice(j, i)] = value; //Oui j puis i car c'est column puis row dans la déclaration
			}
		}

		return new_matrice;
	}

	/*Matrice<1,rows,T> operator*(const Matrice<1, rows, T>& other)
	{
		Matrice<1, rows, T> new_matrice;

		for (int i = 0; i < rows; i++)
		{
			T value = 0;
			for(int j = 0; j < columns; j++)
				value += m_value[GetIndice(j, i)] * other.m_value[i];

			new_matrice.m_value[i] = value;
		}

		return new_matrice;
	}*/

	template<typename T>
		requires(columns == 3 && rows == 3)
	Vector2<T> operator*(const Vector2<T>& vec)
	{
		Vector2<T> new_vec;
		new_vec.x = vec.x * GetValue(0, 0) + vec.y * GetValue(1, 0) + GetValue(2, 0);
		new_vec.y = vec.x * GetValue(0, 1) + vec.y * GetValue(1, 1) + GetValue(2, 1);
		return new_vec;
	}

	template<typename T>
		requires(columns == 4 && rows == 4)
	Vector3<T> operator*(const Vector3<T>& vec)
	{
		Vector3<T> new_vec;
		new_vec.x = vec.x * GetValue(0, 0) + vec.y * GetValue(1, 0) + vec.z * GetValue(2, 0) + GetValue(3, 0);
		new_vec.y = vec.x * GetValue(0, 1) + vec.y * GetValue(1, 1) + vec.z * GetValue(2, 1) + GetValue(3, 1);
		new_vec.z = vec.x * GetValue(0, 2) + vec.y * GetValue(1, 2) + vec.z * GetValue(2, 2) + GetValue(3, 2);
		return new_vec;
	}

	template<typename T>
		requires(columns == 4 && rows == 4)
	Vector4<T> operator*(const Vector4<T>& vec)
	{
		Vector4<T> new_vec;
		new_vec.x = vec.x * GetValue(0, 0) + vec.y * GetValue(1, 0) + vec.z * GetValue(2, 0) + vec.w * GetValue(3, 0);
		new_vec.y = vec.x * GetValue(0, 1) + vec.y * GetValue(1, 1) + vec.z * GetValue(2, 1) + vec.w * GetValue(3, 1);
		new_vec.z = vec.x * GetValue(0, 2) + vec.y * GetValue(1, 2) + vec.z * GetValue(2, 2) + vec.w * GetValue(3, 2);
		new_vec.w = vec.x * GetValue(0, 3) + vec.y * GetValue(1, 3) + vec.z * GetValue(2, 3) + vec.w * GetValue(3, 3);
		return new_vec;
	}
};

#pragma endregion


#pragma region Matrice1xX

template<typename T>
using Mat1x1 = Matrice<1, 1, T>;
template<typename T>
using Mat1x2 = Matrice<1, 2, T>;
template<typename T>
using Mat1x3 = Matrice<1, 3, T>;
template<typename T>
using Mat1x4 = Matrice<1, 4, T>;

using Mat1x1f = Mat1x1<float>;
using Mat1x2f = Mat1x2<float>;
using Mat1x3f = Mat1x3<float>;
using Mat1x4f = Mat1x4<float>;

using Mat1x1i = Mat1x1<int>;
using Mat1x2i = Mat1x2<int>;
using Mat1x3i = Mat1x3<int>;
using Mat1x4i = Mat1x4<int>;

#pragma endregion

#pragma region Matrice2xX

template<typename T>
using Mat2x1 = Matrice<2, 1, T>;
template<typename T>
using Mat2x2 = Matrice<2, 2, T>;
template<typename T>
using Mat2x3 = Matrice<2, 3, T>;
template<typename T>
using Mat2x4 = Matrice<2, 4, T>;

using Mat2x1f = Mat2x1<float>;
using Mat2x2f = Mat2x2<float>;
using Mat2x3f = Mat2x3<float>;
using Mat2x4f = Mat2x4<float>;

using Mat2x1i = Mat2x1<int>;
using Mat2x2i = Mat2x2<int>;
using Mat2x3i = Mat2x3<int>;
using Mat2x4i = Mat2x4<int>;

#pragma endregion

#pragma region Matrice3xX

template<typename T>
using Mat3x1 = Matrice<3, 1, T>;
template<typename T>
using Mat3x2 = Matrice<3, 2, T>;
template<typename T>
using Mat3x3 = Matrice<3, 3, T>;
template<typename T>
using Mat3x4 = Matrice<3, 4, T>;

using Mat3x1f = Mat3x1<float>;
using Mat3x2f = Mat3x2<float>;
using Mat3x3f = Mat3x3<float>;
using Mat3x4f = Mat3x4<float>;

using Mat3x1i = Mat3x1<int>;
using Mat3x2i = Mat3x2<int>;
using Mat3x3i = Mat3x3<int>;
using Mat3x4i = Mat3x4<int>;

#pragma endregion

#pragma region Matrice4xX

template<typename T>
using Mat4x1 = Matrice<4, 1, T>;
template<typename T>
using Mat4x2 = Matrice<4, 2, T>;
template<typename T>
using Mat4x3 = Matrice<4, 3, T>;
template<typename T>
using Mat4x4 = Matrice<4, 4, T>;

using Mat4x1f = Mat4x1<float>;
using Mat4x2f = Mat4x2<float>;
using Mat4x3f = Mat4x3<float>;
using Mat4x4f = Mat4x4<float>;

using Mat4x1i = Mat4x1<int>;
using Mat4x2i = Mat4x2<int>;
using Mat4x3i = Mat4x3<int>;
using Mat4x4i = Mat4x4<int>;

#pragma endregion



template<int nbr, typename T>
Matrice<nbr, nbr, T> Identity()
{
	Matrice<nbr, nbr, T> identity_matrice;
	for (int i = 0; i < nbr; i++)
	{
		for (int j = 0; j < nbr; j++)
		{
			if (i == j)
				identity_matrice.SetValue(j, i, static_cast<T>(1));
		}
	}
	return identity_matrice;
}

template<typename T>
Matrice<4, 4, T> Translate(T tx, T ty, T tz)
{
	Matrice<4, 4, T> translate_matrice = Identity<4, T>();
	translate_matrice.SetValue(3, 0, tx);
	translate_matrice.SetValue(3, 1, ty);
	translate_matrice.SetValue(3, 2, tz);

	return translate_matrice;
}

template<typename T>
Matrice<3, 3, T> Translate(T tx, T ty)
{
	Matrice<3, 3, T> translate_matrice = Identity<3, T>();
	translate_matrice.SetValue(2, 0, tx);
	translate_matrice.SetValue(2, 1, ty);

	return translate_matrice;
}

template<typename T>
Matrice<4, 4, T> Scale(T sx, T sy, T sz)
{
	Matrice<4, 4, T> scale_matrice = Identity<4, T>();
	scale_matrice.SetValue(0, 0, sx);
	scale_matrice.SetValue(1, 1, sy);
	scale_matrice.SetValue(2, 2, sz);

	return scale_matrice;
}

template<typename T>
Matrice<3, 3, T> Scale(T sx, T sy)
{
	Matrice<3, 3, T> scale_matrice = Identity<3, T>();
	scale_matrice.SetValue(0, 0, sx);
	scale_matrice.SetValue(1, 1, sy);

	return scale_matrice;
}

template<typename T>
Matrice<3, 3, T> Rotate(T angle)
{
	Matrice<3, 3, T> rotate_matrice = Identity<3, T>();
	rotate_matrice.SetValue(0, 0, cos(angle));
	rotate_matrice.SetValue(1, 0, -sin(angle));
	rotate_matrice.SetValue(0, 1, sin(angle));
	rotate_matrice.SetValue(1, 1, cos(angle));

	return rotate_matrice;
}

template<typename T>
Matrice<4, 4, T>  RotateX(T angle)
{
	Matrice<4, 4, T> rotate_matrice = Identity<4, T>();
	rotate_matrice.SetValue(1, 1, cos(angle));
	rotate_matrice.SetValue(2, 1, -sin(angle));
	rotate_matrice.SetValue(1, 2, sin(angle));
	rotate_matrice.SetValue(2, 2, cos(angle));

	return rotate_matrice;
}

template<typename T>
Matrice<4, 4, T>  RotateY(T angle)
{
	Matrice<4, 4, T> rotate_matrice = Identity<4, T>();
	rotate_matrice.SetValue(0, 0, cos(angle));
	rotate_matrice.SetValue(0, 2, -sin(angle));
	rotate_matrice.SetValue(2, 0, sin(angle));
	rotate_matrice.SetValue(2, 2, cos(angle));

	return rotate_matrice;
}

template<typename T>
Matrice<4, 4, T>  RotateZ(T angle)
{
	Matrice<4, 4, T> rotate_matrice = Identity<4, T>();
	rotate_matrice.SetValue(0, 0, cos(angle));
	rotate_matrice.SetValue(1, 0, -sin(angle));
	rotate_matrice.SetValue(0, 1, sin(angle));
	rotate_matrice.SetValue(1, 1, cos(angle));

	return rotate_matrice;
}