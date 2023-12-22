#pragma once
#include "pugixml.hpp"
#include <string>

namespace pugi
{
	class xml_document;
}

namespace Pg
{
	class Material;
	class ConstantBufferPropertyList;
	class TexturesPropertyList;
	
	class XMLParser
	{
	public:
		static pugi::xml_document* MakeXMLFromMaterial(Material* mat);
		static void WriteXMLFileToWindows(const std::string& filePath, pugi::xml_document* pugiDoc);

	private:
		static void WriteConstantBufferDataToXML(pugi::xml_node& parentNode, ConstantBufferPropertyList* cbufPropList);
		static void WriteTextureBufferDataToXML(pugi::xml_node& parentNode, TexturesPropertyList* texPropList);
	};
}


