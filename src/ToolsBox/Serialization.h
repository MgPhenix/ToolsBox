/**
* @file Serialization.h
* @brief Tools for saving data in json file
*
* @version 1.0
* @date 2026-10-03
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <string>
#include "vector_l.h"
#include "json_nlohmann.hpp"
using json = nlohmann::json;


class Serializer
{
protected:

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
		in.close();
	}

	//For what we lost
	//template<typename T>
	//T operator[](const std::string& key)
	//auto operator[](const std::string& key) -> std::invoke_result_t<decltype(Get<T>), std::string, T> // Same same but different
	//{
	//	return m_data.value(key, T());
	//}

	auto& operator[](const std::string& key)
	{
		return m_data[key];
	}
};



using Compound = Serializer;

class ITagSerializer
{
private:

	std::string m_fileName;

public:

	std::string GetFileName() { return m_fileName; };
	void SetFileName(const std::string& file_name) { m_fileName = file_name; };

	// Literally WriteToNbtTag from minecraft
	virtual void WriteCompoundTag(Compound& data) = 0;
	// Literally ReadToNbtTag from minecraft
	virtual void ReadCompoundTag(Compound& data) = 0;
};

class SerializerManager
{
private:

	vector_l<ITagSerializer*> m_toUpdate;

	SerializerManager() = default;

public:

	static SerializerManager& GetInstance()
	{
		static SerializerManager instance;
		return instance;
	}

	void UpdateTagWritter()
	{
		for (ITagSerializer* serializer : m_toUpdate)
		{
			Compound c;
			serializer->WriteCompoundTag(c);
			c.Save(serializer->GetFileName());
		}
	}

	void UpdateTagReader()
	{
		for (ITagSerializer* serializer : m_toUpdate)
		{
			Compound c;
			c.Load(serializer->GetFileName());
			serializer->ReadCompoundTag(c);
		}
	}

	void AddTagSerializer(ITagSerializer* serializer) 
	{ 
		m_toUpdate.push_back(serializer); 
	};
};
