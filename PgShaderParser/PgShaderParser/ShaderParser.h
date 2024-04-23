#pragma once
#include <stack>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "PgData.h"

namespace Pg
{
	class Material;
	class VertexShader;
	class PixelShader;

	class ShaderParser
	{
	public:
		ShaderParser();
		~ShaderParser();

		void Initialize();
		void Finalize();

		void CreateNewMaterial(const std::wstring& filePath);
		void CreateVertexShader(const std::wstring& filePath);
		void CreatePixelShader(const std::wstring& filePath);
		//void CopyToXMLFile(const std::wstring& filePath, const std::ifstream& inputFileStream);
		//void SaveToXMLFile(const std::wstring& filePath);
		void ResetAll();
		void ResetMaterial();
		void ResetVertexShader();
		void ResetPixelShader();

	public:
		Material* GetMaterial();
		VertexShader* GetVertexShader();
		PixelShader* GetPixelShader();
		bool* GetIsUseAlphaBlendingPointer();
	private:
		Material* _material = nullptr;
		VertexShader* _editedVS = nullptr;
		PixelShader* _editedPS = nullptr;
		bool _isUseAlphaBlending = false;
	};
}


