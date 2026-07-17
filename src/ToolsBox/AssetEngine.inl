#pragma once
#include "AssetEngine.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

template<typename THeader, typename TEntry>
bool AssetEngine<THeader, TEntry>::LoadFile(const std::string& path,const std::string& customSignature)
{
	m_customSignature = customSignature;

	std::ifstream file(path, std::ios::binary);
	if (!file)
	{
		std::cout << "Can't open file" << std::endl;
		return false;
	}

	THeader header;
	if (!ReadHeader(file, header, customSignature.c_str()))
	{
		std::cout << "Can't read header" << std::endl;
		return false;
	}
	m_version = HeaderTraits<THeader>::GetVersion(header);
	
	TEntry entry;
	while (ReadEntry(file, entry))
	{
		if (EntryTraits<TEntry>::hasFlag)
		{
			if (EntryTraits<TEntry>::GetFlag(entry) == 0x01)
			{
				std::cout << "Detected deleted Entry : " << EntryTraits<TEntry>::GetId(entry) << " will be skip" << std::endl;
				file.seekg(EntryTraits<TEntry>::GetSize(entry), std::ios::cur);
				continue;
			}
		}

		std::string name;
		if (EntryTraits<TEntry>::hasName)
			ReadName(file, entry, name);
		else
			name = std::to_string(EntryTraits<TEntry>::GetId(entry));

		std::vector<byte> data;
		if (!ReadData(file, entry, data))
		{
			std::cout << "Error reading data" << std::endl;
			return false;
		}

		Data<TEntry>* readData = new Data<TEntry>;
		readData->entry = entry;
		readData->data  = std::move(data);

		m_dataMap[name] = readData;
	}

	return true;
}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::SaveInFile(const std::string& path)
{
	LoadFile(path, m_customSignature);

	std::ofstream file(path, std::ios::binary);
	if (!file)
	{
		std::cout << "Can't open file with path : " << path << std::endl;
		return;
	}

	file.write(m_customSignature.c_str(),m_customSignature.size());
	int8 version = m_version;
	file.write(&version, 1);

	TEntry entry;

	for (auto& pair : m_dataMap)
	{
		if (EntryTraits<TEntry>::hasFlag)
		{
			if (EntryTraits<TEntry>::GetFlag(pair.second->entry) == 0x01)
			{
				std::cout << "Entry " << EntryTraits<TEntry>::GetId(pair.second->entry) << " deleted";
				continue;
			}
		}

		uint64 ID = EntryTraits<TEntry>::GetId(pair.second->entry);

		if (ID == 0)
			ID = HashFNV_1A(pair.first);

		EntryTraits<TEntry>::SetId(entry, ID);

		if(EntryTraits<TEntry>::hasEncrypted)
			EntryTraits<TEntry>::SetEncryptionKey(entry, EntryTraits<TEntry>::GetEncryptionKey(pair.second->entry));

		if(EntryTraits<TEntry>::hasName)
			EntryTraits<TEntry>::SetNameSize(	  entry, EntryTraits<TEntry>::GetNameSize(pair.second->entry));

		if(EntryTraits<TEntry>::hasFlag)
			EntryTraits<TEntry>::SetFlag(	      entry, EntryTraits<TEntry>::GetFlag(pair.second->entry));

		if (EntryTraits<TEntry>::hasType)
			EntryTraits<TEntry>::SetType(         entry, EntryTraits<TEntry>::GetType(pair.second->entry));

		std::vector<byte> data;

		if (pair.second->isNew)
		{
			ReadFile(pair.second->path, data);
		}
		else if (pair.second->data.size() != 0)
		{
			data = std::move(pair.second->data);
		}
		else
			continue;

		if (EntryTraits<TEntry>::hasEncrypted)
			data = EncryptData(data, EntryTraits<TEntry>::GetEncryptionKey(pair.second->entry));

		EntryTraits<TEntry>::SetSize(entry, static_cast<int32>(data.size()));

		file.write(reinterpret_cast<char*>(&entry), sizeof(entry));
		
		if (EntryTraits<TEntry>::hasName)		
			file.write(pair.first.data(), EntryTraits<TEntry>::GetNameSize(entry));
		
		file.write(reinterpret_cast<char*>(data.data()), data.size());
	}

	file.close();
}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::EraseData()
{
	for (auto& pair : m_dataMap)
	{
		pair.second->data.clear();
		delete pair.second;
	}

	m_dataMap.clear();
}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::AddData(TEntry& entry, const std::string& id, const std::string& path)
{
	if (m_dataMap.contains(id))
	{
		std::cout << "Data with this id is already registered" << std::endl;
		return;
	}

	Data<TEntry>* data  = new Data<TEntry>;
	data->entry = entry;
	data->isNew = true;
	data->path  = path;

	m_dataMap[id] = data;
}

template<typename THeader, typename TEntry>
bool AssetEngine<THeader, TEntry>::ReadEntry(std::ifstream& file, TEntry& entry)
{
	file.read(reinterpret_cast<char*>(&entry), sizeof(entry));
	
	if (file.gcount() != sizeof(entry))
		return false;

	return true;
}

template<typename THeader, typename TEntry>
bool AssetEngine<THeader, TEntry>::ReadHeader(std::ifstream& file, THeader& header, const char* customSignature)
{
	constexpr size_t size = HeaderTraits<THeader>::signatureSize;
	char signature[size];
	int8 version;

	file.read(signature, size);
	file.read(&version, 1);

	if (file.gcount() == 0 || std::memcmp(signature, customSignature, size) != 0)
	{
		std::cout << "Invalid Signature" << std::endl;
		return false;
	}

	HeaderTraits<THeader>::SetSignature(header, signature);
	HeaderTraits<THeader>::SetVersion(header, version);

	std::cout << "Open file -> version : " << static_cast<int32>(version) << std::endl;
	return true;
}

template<typename THeader, typename TEntry>
bool AssetEngine<THeader, TEntry>::ReadData(std::ifstream& file, TEntry& entry, std::vector<byte>& data)
{
	int32 size = EntryTraits<TEntry>::GetSize(entry);
	if (size == 0)
	{
		std::cout << "Size is 0" << std::endl;
		return false;
	}
	
	data.resize(size);
	file.read(reinterpret_cast<char*>(data.data()), size);

	if (file.gcount() != size)
	{
		std::cout << "Error reading data" << std::endl;
		return false;
	}

	if (EntryTraits<TEntry>::hasEncrypted)
		DecryptData(data, size, EntryTraits<TEntry>::GetEncryptionKey(entry));

	return true;

}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::ReadName(std::ifstream& file, TEntry& entry, std::string& name)
{
	int32 size = EntryTraits<TEntry>::GetNameSize(entry);
	name.resize(size);
	file.read(name.data(), size);
}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::ReadFile(const std::string& path, std::vector<byte>& data)
{
	std::ifstream file(path, std::ios::binary);
	if (!file)
		std::cout << "Can't open file with path : " << path << std::endl;

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	data.resize(static_cast<size_t>(size));
	file.read(reinterpret_cast<char*>(data.data()), size);
	file.close();
}

template<typename THeader, typename TEntry>
void AssetEngine<THeader, TEntry>::DecryptData(std::vector<byte>& data, int32 size, int8 key)
{
	for (int32 i = 0; i < size; i++)
	{
		byte temp = data[i] ^ key;
		data[i] = ((temp >> 3) | (temp << 5));
	}
}

template<typename THeader, typename TEntry>
std::vector<byte> AssetEngine<THeader, TEntry>::EncryptData(std::vector<byte>& data, int8 key)
{
	std::vector<byte> encryptData(data.size());
	for (size_t i = 0; i < data.size(); i++)
	{
		byte temp = ((data[i] << 3) | (data[i] >> 5));
		encryptData[i] = temp ^ key;
	}

	return encryptData;
}

#ifdef ASSET_ENGINE_SDL
template<typename THeader, typename TEntry>
std::unordered_map<std::string, SDL_Surface*> AssetEngine<THeader, TEntry>::ConvertToSDL_Surface()
{
	std::unordered_map<std::string, SDL_Surface*> surfaceMap;

	for (auto pair : m_dataMap)
	{
		SDL_IOStream* rw = SDL_IOFromMem(pair.second->data.data(), static_cast<int>(pair.second->data.size()));
		if (rw == NULL)
		{
			std::cout << "Can't read data to create surface" << std::endl;
			return;
		}

		SDL_Surface* surface = IMG_Load_IO(rw, true);
		if (surface == NULL)
		{
			std::cout << "Can't Create Surface" << std::endl;
			return;
		}
		
		surfaceMap[pair.first] = surface;
	}

	return surfaceMap;
}
#endif // ASSET_ENGINE_SDL

#ifdef ASSET_ENGINE_SFML

template<typename THeader, typename TEntry>
std::unordered_map<std::string, sf::Texture> AssetEngine<THeader, TEntry>::ConvertToSFML_Texture()
{
	std::unordered_map<std::string, sf::Texture> textureMap;

	for (auto& pair : m_dataMap)
	{
		sf::Texture texture;
		if (!texture.loadFromMemory(pair.second->data.data(), pair.second->data.size()))
		{
			std::cout << "Failed to load texture from memory" << std::endl;;
			return;
		}

		textureMap[pair.first] = std::move(texture);
	}

	return textureMap;
}
#endif // ASSET_ENGINE_SFML
