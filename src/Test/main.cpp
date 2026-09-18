#include "ToolsBox.h"
#include <iostream>
#include <functional>
#include <unordered_map>

#include "unordered_map_l.h"


int main()
{
	float ilist[] = {
		1.f, 0.f, 0.f, 1.f
	};
	Matrice<1, 4, float> point = Matrice<1, 4, float>(ilist);
	//auto rotation = RotateZ(1.5708f);
	//Matrice<1, 4, float> result = rotation * mat3;
	
	auto T = Translate(10.f, 5.f, 2.f);
	auto R = RotateZ(1.5708f);
	auto S = Scale(2.f, 2.f, 2.f);
	
	auto M = R * T * S;

	Vector3<float> p = { 1.f, 0.f, 0.f };
	auto result = R * p;


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