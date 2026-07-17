#pragma once
#include <unordered_map>
#include <vector>
#include "PrimitiveTypes.h"
#include <string>

#if defined(SDL_VERSION) && !defined(ASSET_ENGINE_SDL)
	#define ASSET_ENGINE_SDL
#endif
#if defined(SFML_VERSION_MAJOR) && !defined(ASSET_ENGINE_SFLM)
	#define ASSET_ENGINE_SFML
#endif

#ifdef ASSET_ENGINE_SDL
	#include <SDL3/SDL.h>
	#include <SDL3_image/SDL_image.h>
#endif

#ifdef ASSET_ENGINE_SFML
	#include <SFML/Graphics.hpp>
#endif


template<typename THeader>
struct HeaderTraits
{
	static const char* GetSignature(const THeader& header) { return header.signature; };
	static int8        GetVersion(const THeader& header)   { return header.version;   };

	static constexpr size_t signatureSize = 1;

	static void SetSignature(THeader& header, const char* _signature) { std::memcpy(header.signature, _signature, signatureSize); };
	static void SetVersion(THeader& header, int8 _version)            { header.version = _version; };

	static constexpr bool hasOffset = false;
	static uint32 GetOffset() { return 0; };
};

template<typename TEntry>
struct EntryTraits
{
	static int32  GetSize(const TEntry& entry) { return entry.size; };
	static uint64 GetId(const TEntry& entry)   { return entry.id;   };

	static void SetSize(TEntry& entry, int32 _size) { entry.size = _size; };
	static void SetId(TEntry& entry, uint64 _id)    { entry.id   = _id;   };

	static constexpr bool hasEncrypted = false;
	static constexpr bool hasName	   = false;
	static constexpr bool hasFlag	   = false;
	static constexpr bool hasType	   = false;

	static int8  GetEncryptionKey(const TEntry& entry) { return 0; };
	static int32 GetNameSize(const TEntry& entry)      { return 0; };
	static int8  GetFlag(const TEntry& entry)          { return 0; };
	static int64 GetType(const TEntry& entry)		   { return 0; };

	static void  SetEncryptionKey(TEntry& entry, int8 _key)  { return; };
	static void  SetNameSize(TEntry& entry, int32 _nameSize) { return; };
	static void  SetFlag(TEntry& entry, int8 _flag)		     { return; };
	static void  SetType(TEntry& entry, int64 _type)         { return; };
};


struct DefaultEntry
{
	int8   key;
	uint64 id;
	int32  nameSize;
	int8   flag;
	int64  type;
	int16  width;
	int16  height;
	int32  size;
};

struct DefaultHeader
{
	char signature[4];
	int8 version;
};

template<>
struct EntryTraits<DefaultEntry>
{
	static int32  GetSize(const DefaultEntry& entry) { return entry.size; };
	static uint64 GetId(const DefaultEntry& entry)   { return entry.id;   };

	static void  SetSize(DefaultEntry& entry, int32 _size) { entry.size = _size; };
	static void  SetId(DefaultEntry& entry, uint64 _id)    { entry.id   = _id;   };

	static constexpr bool hasEncrypted = true;
	static constexpr bool hasName      = true;
	static constexpr bool hasFlag      = true;
	static constexpr bool hasType      = true;

	static int8  GetEncryptionKey(const DefaultEntry& entry) { return entry.key;	  };
	static int32 GetNameSize(const DefaultEntry& entry)      { return entry.nameSize; };
	static int8  GetFlag(const DefaultEntry& entry)          { return entry.flag;	  };
	static int64 GetType(const DefaultEntry& entry)          { return entry.type;	  };

	static void  SetEncryptionKey(DefaultEntry& entry, int8 _key)	{ entry.key		 = _key;	  };
	static void  SetNameSize(DefaultEntry& entry, int32 _nameSize)  { entry.nameSize = _nameSize; };
	static void  SetFlag(DefaultEntry& entry, int8 _flag)			{ entry.flag	 = _flag;	  };
	static void  SetType(DefaultEntry& entry, int64 _type)			{ entry.type	 = _type;	  };
};

template<>
struct HeaderTraits<DefaultHeader>
{
	static const char* GetSignature(const DefaultHeader& header) { return header.signature; };
	static int8        GetVersion(const DefaultHeader& header)	 { return header.version;   };

	static constexpr size_t signatureSize = 4;

	static void SetSignature(DefaultHeader& header, const char* _signature) { std::memcpy(header.signature, _signature, signatureSize); };
	static void SetVersion(DefaultHeader& header, int8 _version)			{ header.version = _version; };

	static constexpr bool hasOffset = false;
	static uint32 GetOffset() { return 0; };
};

template<typename TEntry>
struct Data
{
	TEntry			  entry;
	std::vector<byte> data;
	std::string       path;
	bool              isNew = false;
};

template<
	typename THeader = DefaultHeader, 
	typename TEntry = DefaultEntry
>
class AssetEngine
{
private:

	std::unordered_map<std::string, Data<TEntry>*> m_dataMap;

	std::string m_customSignature;
	int8		m_version;

public:

	bool LoadFile(const std::string& path, const std::string& customSignature);
	void SaveInFile(const std::string& path);

	void EraseAllData();
	
	void AddData(TEntry& entry,const std::string& id, const std::string& path);

private:

	bool ReadEntry(std::ifstream& file, TEntry& entry);
	bool ReadHeader(std::ifstream& file, THeader& header, const char* customSignature);
	bool ReadData(std::ifstream& file, TEntry& entry, std::vector<byte>& data);
	void ReadName(std::ifstream& file, TEntry& entry, std::string& name);
	void ReadFile(const std::string& path, std::vector<byte>& data);

	void DecryptData(std::vector<byte>& data, int32 size, int8 key);
	std::vector<byte> EncryptData(std::vector<byte>& data, int8 key);

public:

#ifdef ASSET_ENGINE_SDL

	std::unordered_map<std::string, SDL_Surface*> ConvertToSDL_Surface();

#endif // ASSET_ENGINE_SDL

#ifdef ASSET_ENGINE_SFML

	std::unordered_map<std::string, sf::Texture> ConvertToSFML_Texture();

#endif // ASSET_ENGINE_SFML
};

#include "AssetEngine.inl"