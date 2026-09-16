#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

#include "unordered_map_l.h"


template<int columns, int rows, typename T>
class Matrice
{
protected:

	T m_value[columns * rows];

	int m_size = 0;

public:

	int GetIndice(int column, int row) { return row * columns + column; };

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
		m_size(columns * rows)
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
					value += m_value[GetIndice(k, i)] * other.m_value[GetIndice(j, k)];

				new_matrice.m_value[GetIndice(j, i)] = value; //Oui j puis i car c'est column puis row dans la déclaration
			}
		}

		return new_matrice;
	}

	Matrice<1,rows,T> operator*(const Matrice<1, rows, T>& other)
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
	}

	Vector2<T> operator*(const Vector2<T>& vec)
	{
		Vector2<T> new_vec;
		new_vec.x = vec.x * m_value[0] + vec.x * m_value[1];
		new_vec.y = vec.y * m_value[2] + vec.y * m_value[3];
		return new_vec;
	}
};

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


using Mat1x1f = Matrice<1, 1, float>;
using Mat2x1f = Matrice<2, 1, float>;
using Mat1x2f = Matrice<1, 2, float>;
using Mat2x2f = Matrice<2, 2, float>;
using Mat2x3f = Matrice<2, 3, float>;
using Mat3x3f = Matrice<3, 3, float>;

using Mat4x4f = Matrice<4, 4, float>;
using Mat4x4i = Matrice<4, 4, int>;
using Mat2x2i = Matrice<2, 2, int>;

int main()
{
	int ilist[] = {
		4, 2,
		6, 1
	};
	Mat2x2i mat3 = Mat2x2i(ilist);

	Mat4x4i identity = Identity<4, int>();

	float list[] = {
		2.f, 2.f, 5.f, 6.f,
		1.f, 0.f, 9.f, 2.f,
		8.f, 7.f, 4.f, 1.f,
		4.f, 5.f, 2.f, 2.f
	};
	Mat4x4f mat2 = Mat4x4f(list);
	mat2.SetValue(0, 1, 1.f);

	Mat4x4f mat;
	mat.SetValue(0, 1, 29.f);
	mat(0, 1) = 32.f;
	Mat4x4f new_mat = mat * mat2;
	float f = new_mat(0, 1);
	std::cout << f << std::endl;
}





















//MyUnorderedMap<std::string, int> map;
//map.TempAdd(new Node<std::string, int>(std::string("test"), 5, nullptr));
//int test = map["test"];
//std::cout << test << std::endl;

//MyUnorderedMap<std::string, int> map2 = map;
//std::string truc = "truc";
//map2.insert(truc, 8);
////map2["truc"] = 34;
//int test2 = map2["truc"];
//std::cout << test2 << std::endl;




//MyAllocator<float> alloc;

//using ReboundAllocType = MyAllocator<float>::rebind<Node>::other;
//ReboundAllocType allocNode;

//Node* n = allocNode.allocate(1);
//new (n) Node{ 42, 3.14f };

//std::cout << "Key : " << n->key << " | Value : " << n->value << std::endl;
//n->~Node();
//allocNode.deallocate(n, 1);
//return 0;


//int main()
//{
//	Test* mem = static_cast<Test*>(::operator new(3 * sizeof(Test)));
//
//	std::cout << mem[0].x << std::endl; //Print n'importe quoi 
//
//	new (&mem[0]) Test();
//
//	std::cout << mem[0].x << std::endl; //Print n'importe quoi 
//
//	mem[0].~Test();
//
//	::operator delete(mem);
//
//
//	return 0;
//}