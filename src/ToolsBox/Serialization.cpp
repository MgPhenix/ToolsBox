#include "Serialization.h"
#include <fstream>
#include <iostream>

json& Serializer::GetData()
{
	return m_data;
};

void Serializer::Save(const std::string& path)
{
	std::ofstream out(path);
	out << m_data.dump(4);
	out.close();
}

void Serializer::Load(const std::string& path)
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

std::string ITagSerializer::GetFileName()
{
	return m_fileName;
};

void ITagSerializer::SetFileName(const std::string& file_name)
{
	m_fileName = file_name;
};

SerializerManager& SerializerManager::GetInstance()
{
	static SerializerManager instance;
	return instance;
}


void SerializerManager::UpdateTagWritter()
{
	for (ITagSerializer* serializer : m_toUpdate)
	{
		Compound c;
		serializer->WriteCompoundTag(c);
		c.Save(serializer->GetFileName());
	}
}

void SerializerManager::UpdateTagReader()
{
	for (ITagSerializer* serializer : m_toUpdate)
	{
		Compound c;
		c.Load(serializer->GetFileName());
		serializer->ReadCompoundTag(c);
	}
}

void SerializerManager::AddTagSerializer(ITagSerializer* serializer)
{
	m_toUpdate.push_back(serializer);
};
