#include "ShaderParser.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Material.h"
#include <cassert>

namespace Pg
{
	ShaderParser::ShaderParser()
	{

	}

	ShaderParser::~ShaderParser()
	{

	}

	void ShaderParser::Initialize()
	{

	}

	void ShaderParser::Finalize()
	{
		ResetAll();
	}

	void ShaderParser::CreateNewMaterial(const std::wstring& filePath)
	{
		//호출시점에서 
		ResetMaterial();
		_material = new Material();
		_material->SetFilePath(filePath);
		_material->SetVertexShader(_editedVS);
		_material->SetPixelShader(_editedPS);
		_material->Generate(filePath);
	}

	void ShaderParser::CreateVertexShader(const std::wstring& filePath)
	{
		ResetVertexShader();
		_editedVS = new VertexShader(filePath);
	}

	void ShaderParser::CreatePixelShader(const std::wstring& filePath)
	{
		ResetPixelShader();
		_editedPS = new PixelShader(filePath);
	}

	//void ShaderParser::CopyToXMLFile(const std::wstring& filePath, const std::ifstream& inputFileStream)
	//{
	//
	//}
	//
	//void ShaderParser::SaveToXMLFile(const std::wstring& filePath)
	//{
	//
	//}

	void ShaderParser::ResetMaterial()
	{
		if (_material != nullptr)
		{
			delete _material;
			_material = nullptr;
		}
		assert(_material == nullptr);
	}

	void ShaderParser::ResetVertexShader()
	{
		if (_editedVS != nullptr)
		{
			delete _editedVS;
			_editedVS = nullptr;
		}

		assert(_editedVS == nullptr);
	}

	void ShaderParser::ResetPixelShader()
	{
		if (_editedPS != nullptr)
		{
			delete _editedPS;
			_editedPS = nullptr;
		}
		assert(_editedPS == nullptr);
	}

	void ShaderParser::ResetAll()
	{
		ResetMaterial();
		ResetVertexShader();
		ResetPixelShader();
	}

	Pg::Material* ShaderParser::GetMaterial()
	{
		return _material;
	}

	Pg::VertexShader* ShaderParser::GetVertexShader()
	{
		return _editedVS;
	}

	Pg::PixelShader* ShaderParser::GetPixelShader()
	{
		return _editedPS;
	}

}