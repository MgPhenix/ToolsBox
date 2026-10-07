/**
* @file Serialization.h
* @brief Tools for saving data in json file
*
* @version 1.1
* @date 2026-10-03
*
* @copyright idk bro
* @author MgPhenix (https://github.com/MgPhenix)
*/
#pragma once
#include <string>
#include "vector_l.h"
#include "json_nlohmann.hpp"
/**
* @brief nlohmann json data type
*/
using json = nlohmann::json;

/**
* @brief A simple Serializer for write/read data to/from a json file
*/
class Serializer
{
protected:

	json m_data;

public:

	Serializer() = default;

	/**
	* @brief Write data in a json file
	* @param std::string& id : Id of the data you wanna save
	* @tparam T : Value you wanna save
	*/
	template<typename T>
	void Write(const std::string& id, T value)
	{
		m_data[id] = value;
	}
	/**
	* @brief Read data from a json file
	* @param std::string& id : Id of the data you wanna read
	* @tparam T& : Value you wanna read
	*/
	template<typename T>
	void Read(const std::string& id, T& value)
	{
		value = m_data.value(id, T());
	}
	/**
	* @brief Read data from a json file (use Get<type>(id) )
	* @param std::string& id : Id of the data you wanna read
	* @return T : value you wanna read 
	*/
	template<typename T>
	T Get(const std::string& id)
	{
		return m_data.value(id, T());
	}

public:

	/**
	* @brief Get raw json data (nlohmann json)
	* @return json& : reference to the raw json data
	*/
	json& GetData();
	/**
	* @brief Save Data to a file
	* @param const std::string& path : Path to your json file
	*/
	void Save(const std::string& path);
	/**
	* @brief Load Data from a file
	* @param const std::string& path : Path to your json file
	*/
	void Load(const std::string& path);

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


/**
* @brief Just a different name for Serializer
*/
using Compound = Serializer;

/**
* @brief Interface for serializing data from a class 
*/
class ITagSerializer
{
private:

	std::string m_fileName;

public:

	/**
	* @brief Get the path to the json file
	* @return std::string : path to the json file
	*/
	std::string GetFileName();
	/**
	* @brief Set the path to the json file data will be write/read
	*/
	void SetFileName(const std::string& file_name);
	/**
	* @brief Write data in a Compound storage (function will be call by SerializerManager)
	* @param Compound& data : Write everything you want in this compound, don't forget to set the file name with SetFileName() before
	*/
	virtual void WriteCompoundTag(Compound& data) = 0; // Literally WriteToNbtTag from minecraft
	/**
	* @brief Read data from a Compound storage (function will be call by SerializerManager)
	* @param Compound& data : Read everything you want from this compound, don't forget to set the file name with SetFileName() before
	*/
	virtual void ReadCompoundTag(Compound& data) = 0; // Literally ReadToNbtTag from minecraft
};

class SerializerManager
{
private:

	vector_l<ITagSerializer*> m_toUpdate;

	SerializerManager() = default;

public:
	/**
	* @brief Get SerializerManager singleton
	*/
	static SerializerManager& GetInstance();
	/**
	* @brief Call WriteCompoundTag() for every ITagSerializer 
	*/
	void UpdateTagWritter();
	/**
	* @brief Call ReadCompoundTag() for every ITagSerializer
	*/
	void UpdateTagReader();
	/**
	* @brief Add a ITagSerializer to the "to update" list
	* @param ITagSerializer* serializer : serializer you want to add
	*/
	void AddTagSerializer(ITagSerializer* serializer);
};
