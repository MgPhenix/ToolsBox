#pragma once
#include "AssetEngine.h"
#include <iostream>
#include <fstream>

template<typename THeader, typename TEntry>
bool AssetEngine<THeader, TEntry>::LoadFile(const std::string& path, const char* customSignature)
{
	std::ifstream file(path, std::ios::binary);
	if (!file)
	{
		std::cout << "Can't open file" << std::endl;
		return false;
	}

	THeader header;
	if (!ReadHeader(file, header, customSignature))
	{
		std::cout << "Can't read header" << std::endl;
		return false;
	}
	
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
void AssetEngine<THeader, TEntry>::DecryptData(std::vector<byte>& data, int32 size, int8 key)
{
	for (int32 i = 0; i < size; i++)
	{
		byte temp = data[i] ^ key;
		data[i] = ((temp >> 3) | (temp << 5));
	}
}

#ifdef ASSET_ENGINE_SDL
template<typename THeader, typename TEntry>
std::unordered_map<std::string, SDL_Surface*> AssetEngine<THeader, TEntry>::ConvertToSDL_Surface()
{
	std::unordered_map<std::string, SDL_Surface*> surfaceMap;

	for (auto pair : m_dataMap)
	{
		SDL_IOStream* rw = SDL_IOFromMem(pair.second.data, static_cast<int>(pair.second.data.size()));
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
#endif
