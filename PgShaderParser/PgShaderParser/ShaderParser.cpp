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

	void ShaderParser::CreateMaterial(const std::wstring& filePath)
	{
		ResetMaterial();
		_material = new Material();
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

	void ShaderParser::CopyToXMLFile(const std::wstring& filePath, const std::ifstream& inputFileStream)
	{

	}

	void ShaderParser::SaveToXMLFile(const std::wstring& filePath)
	{

	}

	void ShaderParser::ResetMaterial()
	{
		if (_material != nullptr)
		{
			delete _material;
		}
	}

	void ShaderParser::ResetVertexShader()
	{
		if (_editedVS != nullptr)
		{
			delete _editedVS;
		}
	}

	void ShaderParser::ResetPixelShader()
	{
		if (_editedPS != nullptr)
		{
			delete _editedPS;
		}
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