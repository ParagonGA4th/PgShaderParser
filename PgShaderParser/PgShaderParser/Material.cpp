#include "Material.h"
#include "XMLParser.h"
#include "TextHelper.h"
#include <cassert>
#include <filesystem>

#include "pugixml.hpp"

namespace Pg
{
	Material::Material()
	{

	}

	Pg::VertexShader* Material::ConfideGetVertexShader()
	{
		//�ִٴ� ���� �̹� Ȯ������ ȣ���� �Լ�.
		assert(_vs != nullptr);
		return _vs;
	}

	Pg::PixelShader* Material::ConfideGetPixelShader()
	{
		//�ִٴ� ���� �̹� Ȯ������ ȣ���� �Լ�.
		assert(_ps != nullptr);
		return _ps;
	}

	bool Material::Generate(const std::wstring& filePath)
	{
		pugi::xml_document* tXMLDoc = XMLParser::MakeXMLFromMaterial(this);
		XMLParser::WriteXMLFileToWindows(TextHelper::WStringToAnsi(filePath), tXMLDoc);
		return true;
	}

	void Material::SetFilePath(const std::wstring& fPath)
	{
		_filePath = fPath;
	}

	std::wstring Material::GetFilePath()
	{
		return _filePath;
	}

	std::wstring Material::GetFileName()
	{
		return std::filesystem::path(_filePath).filename();
	}

}