/**
* @file Serialization.h
* @brief 
*
* @version 1.0
* @date 2026-10-03
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <string>
#include "json_nlohmann.hpp"
using json = nlohmann::json;


class Serializer
{
private:

	std::string main_id;

	json m_data;

public:

	Serializer() = default;

	template<typename T>
	void Write(const std::string& id, T value)
	{
		m_data[id] = value;
	}

	template<typename T>
	void Read(const std::string& id, T& value)
	{
		value = m_data.value(id, T());
	}

	template<typename T>
	T Get(const std::string& id)
	{
		return m_data.value(id, T());
	}

public:

	json& GetData() { return m_data; };

	void Save(const std::string& path)
	{
		std::ofstream out(path);
		out << m_data.dump(4);
		out.close();
	}

	void Load(const std::string& path)
	{
		std::ifstream in(path);
		if (!in.is_open())
		{
			std::cout << "Error path doesn't exist" << std::endl;
			return;
		}

		m_data = json::parse(in);
	}
};



































//class Compound
//{
//
//};
//
//
//class ISerializer
//{
//	template<typename... Args>
//	void Serialize(const Compound& data, Args&&... arg) = 0;
//
//	template<typename... Args>
//	void Deserialize(const Compound& data, Args&&... arg) = 0;
//};

