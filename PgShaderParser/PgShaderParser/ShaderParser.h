#pragma once
#include <stack>
#include <string>
#include <filesystem>

#include "PgData.h"

namespace Pg
{
	class Material;

	class ShaderParser
	{
	public:
		ShaderParser();
		~ShaderParser();

		void Initialize();
		void Finalize();

		Material* GetMaterial();

		std::wstring GetCurrentVertexShaderPath();
		std::wstring GetCurrentPixelShaderPath() { return _currentPSPath; }
		std::wstring GetCurrentMaterialPath() { return _currentMaterialPath; }

		void ActivateVertexShaderPath(const std::wstring& path) { _currentVSPath = path; }
		void ActivatePixelShaderPath(const std::wstring& path) { _currentPSPath = path; }
		void ActivateMaterialPath(const std::wstring& path) { _currentMaterialPath = path; }

		std::wstring GetCurrentVertexShaderName() { return std::filesystem::path(_currentVSPath).filename().generic_wstring(); }
		std::wstring GetCurrentPixelShaderName() { return std::filesystem::path(_currentPSPath).filename().generic_wstring(); }
		std::wstring GetCurrentMaterialName() { return std::filesystem::path(_currentMaterialPath).filename().generic_wstring(); }

		bool HasActiveVertexShaderPath() { return _isNowAffectVertexShader; }
		bool HasActivePixelShaderPath() { return _isNowAffectPixelShader;	}
		bool HasActiveMaterialPath() { return _isNowAffectMaterial;			}

	private:
		//std::wstring _currentVSPath;
		//std::wstring _currentPSPath;
		//std::wstring _currentMaterialPath;
		//
		//bool _isNowAffectVertexShader = true;
		//bool _isNowAffectPixelShader = true;
		//bool _isNowAffectMaterial = true;

		Material* _material = nullptr;

	
	};
}


