#pragma once
#include <unordered_map>
#include <vector>
#include "PrimitiveTypes.h"
#include <string>


/*
Dans l'idée j'aimerais un truc du style

struct MyHeader
struct MyEntry

AM = AssetEngine::GetInstance()

AM.ReadHead<MyHeader>()
AM.ReadEntry<MyEntry>()

*/

struct Header
{
};

struct Entry
{
};

class AssetEngine
{
private:

	std::unordered_map<std::string, std::vector<byte>> test;

public:



};

