#include "XMLParser.h"
#include "Material.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "TextHelper.h"
#include "ConstantBufferPropertyList.h"
#include "TexturesPropertyList.h"
#include "EnumHelper.h"

#include <iostream>

namespace Pg
{
	pugi::xml_document* XMLParser::MakeXMLFromMaterial(Material* mat)
	{
		//XML Document 형태 생성.
		pugi::xml_document* doc = new pugi::xml_document;
		pugi::xml_node rootNode = doc->append_child("PgMaterial");
		{
			// 첫 분류 = Vertex Shader.
			VertexShader* vs = mat->ConfideGetVertexShader();
			pugi::xml_node vsNode = rootNode.append_child("VertexShader");
			{
				//파일 이름 저장용.
				pugi::xml_node vsName = vsNode.append_child("FileName");
				vsName.append_child(pugi::node_pcdata).set_value(TextHelper::WStringToAnsi(vs->GetFileName()).c_str());
			}
			//VS : Constant Buffer 수를 하나로 고정.
			WriteConstantBufferDataToXML(vsNode, vs->_matPropConstantBufferList.get());
			WriteTextureBufferDataToXML(vsNode, vs->_matPropTexturesList.get());
		}
		{
			// 두번째 = Pixel Shader.
			PixelShader* ps = mat->ConfideGetPixelShader();
			pugi::xml_node psNode = rootNode.append_child("PixelShader");
			{
				//파일 이름 저장용.
				pugi::xml_node psName = psNode.append_child("FileName");
				psName.append_child(pugi::node_pcdata).set_value(TextHelper::WStringToAnsi(ps->GetFileName()).c_str());
			}
			//VS : Constant Buffer 수를 하나로 고정.
			WriteConstantBufferDataToXML(psNode, ps->_matPropConstantBufferList.get());
			WriteTextureBufferDataToXML(psNode, ps->_matPropTexturesList.get());
		}
		//디버깅용.
		doc->print(std::cout);
		return doc;
	}

	void XMLParser::WriteXMLFileToWindows(const std::string& filePath, pugi::xml_document* pugiDoc)
	{
		std::cout << "Saving result: " << pugiDoc->save_file(filePath.c_str()) << std::endl;
	}

	void XMLParser::WriteConstantBufferDataToXML(pugi::xml_node& parentNode, ConstantBufferPropertyList* cbufPropList)
	{
		pugi::xml_node cbufferNode = parentNode.append_child("ConstantBuffer");
		ConstantBufferPropertyList* cbPropList = cbufPropList;
		{
			pugi::xml_node cbufferNameNode = cbufferNode.append_child("BufferName");
			cbufferNameNode.append_child(pugi::node_pcdata).set_value(cbPropList->GetConstantBufferName().c_str());
		}
		{
			pugi::xml_node cbufferSizeNode = cbufferNode.append_child("ByteCount");
			cbufferSizeNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->GetByteCount()).c_str());
		}
		{
			pugi::xml_node cbufferRegisterNode = cbufferNode.append_child("RegisterCount");
			cbufferRegisterNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->GetRegisterNumberCount()).c_str());
		}

		{
			pugi::xml_node cbufferVariableOrderNode = cbufferNode.append_child("VariableOrder");

			for (int i = 0; i < cbufPropList->_varRecord.size(); i++)
			{
				pugi::xml_node tVarOrder = cbufferVariableOrderNode.append_child(std::to_string(i).c_str());
				cbufferVariableOrderNode.append_child(pugi::node_pcdata).set_value(cbPropList->_varRecord[i].c_str());
			}
		}

		//// Constant Buffer 아래에 변수 이름 추가.
		pugi::xml_node cbufferVarNode = cbufferNode.append_child("Variables");

		int totalVarCount = 0;
		//Bool Part.
		for (int i = 0; i < cbPropList->_boolPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_boolPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "bool";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_boolPropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_boolPropList[i].first._startOffset;

			pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
			varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(static_cast<int>(cbPropList->_boolPropList[i].second)).c_str());
		}
		totalVarCount += cbPropList->_boolPropList.size();

		for (int i = 0; i < cbPropList->_uintPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_uintPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "uint";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_uintPropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_uintPropList[i].first._startOffset;

			pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
			varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_uintPropList[i].second).c_str());
		}
		totalVarCount += cbPropList->_uintPropList.size();

		for (int i = 0; i < cbPropList->_intPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_intPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "int";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_intPropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_intPropList[i].first._startOffset;

			pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
			varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_intPropList[i].second).c_str());
		}
		totalVarCount += cbPropList->_intPropList.size();

		for (int i = 0; i < cbPropList->_floatPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_floatPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "float";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_floatPropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_floatPropList[i].first._startOffset;

			pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
			varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_floatPropList[i].second).c_str());
		}
		totalVarCount += cbPropList->_floatPropList.size();

		for (int i = 0; i < cbPropList->_vec2PropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_vec2PropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "float2";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_vec2PropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_vec2PropList[i].first._startOffset;

			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec2PropList[i].second.x).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("y");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec2PropList[i].second.y).c_str());
			}
		}
		totalVarCount += cbPropList->_vec2PropList.size();

		for (int i = 0; i < cbPropList->_vec3PropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_vec3PropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "float3";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_vec3PropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_vec3PropList[i].first._startOffset;

			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec3PropList[i].second.x).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("y");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec3PropList[i].second.y).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("z");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec3PropList[i].second.z).c_str());
			}
		}
		totalVarCount += cbPropList->_vec3PropList.size();

		for (int i = 0; i < cbPropList->_vec4PropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = cbufferVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = cbPropList->_vec4PropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "float4";
			cbufferVarExampleNode.append_attribute("Size") = cbPropList->_vec4PropList[i].first._size;
			cbufferVarExampleNode.append_attribute("StartOffset") = cbPropList->_vec4PropList[i].first._startOffset;

			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("x");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec4PropList[i].second.x).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("y");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec4PropList[i].second.y).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("z");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec4PropList[i].second.z).c_str());
			}
			{
				pugi::xml_node varValueNode = cbufferVarExampleNode.append_child("w");
				varValueNode.append_child(pugi::node_pcdata).set_value(std::to_string(cbPropList->_vec4PropList[i].second.w).c_str());
			}
		}
		totalVarCount += cbPropList->_vec4PropList.size();
	}

	void XMLParser::WriteTextureBufferDataToXML(pugi::xml_node& parentNode, TexturesPropertyList* texPropList)
	{
		pugi::xml_node textureNode = parentNode.append_child("Textures");

		{
			pugi::xml_node tVariableOrderNode = textureNode.append_child("VariableOrder");

			for (int i = 0; i < texPropList->_varRecord.size(); i++)
			{
				pugi::xml_node tVarOrder = tVariableOrderNode.append_child(std::to_string(i).c_str());
				tVariableOrderNode.append_child(pugi::node_pcdata).set_value(texPropList->_varRecord[i].c_str());
			}
		}

		pugi::xml_node textureVarNode = textureNode.append_child("Variables");
		int totalVarCount = 0;

		for (int i = 0; i < texPropList->_texture1DPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = textureVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = texPropList->_texture1DPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "Texture1D";
			cbufferVarExampleNode.append_attribute("ResourceReturnType") = EnumHelper::ToString(texPropList->_texture1DPropList[i].first._resReturnType).c_str();
			cbufferVarExampleNode.append_attribute("RegisterCount") = std::to_string(texPropList->_texture1DPropList[i].first._registerCnt).c_str();
			cbufferVarExampleNode.append_attribute("Value") = texPropList->_texture1DPropList[i].second.c_str();
		}
		totalVarCount += texPropList->_texture1DPropList.size();

		for (int i = 0; i < texPropList->_texture2DPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = textureVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = texPropList->_texture2DPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "Texture2D";
			cbufferVarExampleNode.append_attribute("ResourceReturnType") = EnumHelper::ToString(texPropList->_texture2DPropList[i].first._resReturnType).c_str();
			cbufferVarExampleNode.append_attribute("RegisterCount") = std::to_string(texPropList->_texture2DPropList[i].first._registerCnt).c_str();
			cbufferVarExampleNode.append_attribute("Value") = texPropList->_texture2DPropList[i].second.c_str();
		}
		totalVarCount += texPropList->_texture2DPropList.size();

		for (int i = 0; i < texPropList->_texture2DArrayPropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = textureVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = texPropList->_texture2DArrayPropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "Texture2DArray";
			cbufferVarExampleNode.append_attribute("ResourceReturnType") = EnumHelper::ToString(texPropList->_texture2DArrayPropList[i].first._resReturnType).c_str();
			cbufferVarExampleNode.append_attribute("RegisterCount") = std::to_string(texPropList->_texture2DArrayPropList[i].first._registerCnt).c_str();
			cbufferVarExampleNode.append_attribute("Value") = texPropList->_texture2DArrayPropList[i].second.c_str();
		}
		totalVarCount += texPropList->_texture2DArrayPropList.size();

		for (int i = 0; i < texPropList->_textureCubePropList.size(); i++)
		{
			//파싱해서 읽어들일 때 -> Index를 노드의 이름으로 저장해서 늘어날 여지가 있게 한다.
			pugi::xml_node cbufferVarExampleNode = textureVarNode.append_child(std::to_string(i + totalVarCount).c_str());
			cbufferVarExampleNode.append_attribute("Name") = texPropList->_textureCubePropList[i].first._name.c_str();
			cbufferVarExampleNode.append_attribute("Type") = "TextureCube";
			cbufferVarExampleNode.append_attribute("ResourceReturnType") = EnumHelper::ToString(texPropList->_textureCubePropList[i].first._resReturnType).c_str();
			cbufferVarExampleNode.append_attribute("RegisterCount") = std::to_string(texPropList->_textureCubePropList[i].first._registerCnt).c_str();
			cbufferVarExampleNode.append_attribute("Value") = texPropList->_textureCubePropList[i].second.c_str();
		}
		totalVarCount += texPropList->_textureCubePropList.size();

	}

}
