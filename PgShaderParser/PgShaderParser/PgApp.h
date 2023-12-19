#pragma once
#include <fstream>
#include <filesystem>
#include <cassert>
#include <string>
#include <memory>

#include "PgEnums.h"

namespace Pg
{
	class ShaderParser;

	class PgApp
	{
	public:
		PgApp();
		~PgApp();
	public:
		//Main
		void Initialize();
		void Loop();
		void Finalize();

	public:
		//IMGUI¿Í ±³·ù
		void OpenShaderButtonPressed(eShaderType shaderType);
		void SaveMaterialButtonPressed();
		void NewMaterialButtonPressed();
		void SaveAsMaterialButtonPressed();
		void OpenMaterialButtonPressed();
		void ResetEditorButtonPressed();
		void ResetVertexShaderButtonPressed();
		void ResetPixelShaderButtonPressed();

		std::wstring GetCurrentVertexShaderPath() { return _currentVSPath; }
		std::wstring GetCurrentPixelShaderPath() { return _currentPSPath; }
		std::wstring GetCurrentMaterialPath() { return _currentMaterialPath; }

		std::wstring GetCurrentVertexShaderName() { return std::filesystem::path(_currentVSPath).filename().generic_wstring(); }
		std::wstring GetCurrentPixelShaderName() {	return std::filesystem::path(_currentPSPath).filename().generic_wstring(); }
		std::wstring GetCurrentMaterialName() {	return std::filesystem::path(_currentMaterialPath).filename().generic_wstring(); }

		bool IsNowAffectVertexShaderPath() { return _isNowAffectVertexShader; }
		bool IsNowAffectPixelShaderPath() { return _isNowAffectPixelShader; }
		bool IsNowAffectMaterialPath() { return _isNowAffectMaterial; }

	private:
		void ShowOpenShaderDialog(eShaderType shaderType);
		void ShowSaveMaterialDialog();
		void ShowNewMaterialDialog();
		void ShowSaveAsMaterialDialog();
		void ShowOpenMaterialDialog();

		void ResetEditor();
		void ResetVS();
		void ResetPS();

	private:
		std::unique_ptr<ShaderParser> _shaderParser;

	private:
		std::wstring _currentVSPath;
		std::wstring _currentPSPath;
		std::wstring _currentMaterialPath;

		bool _isNowAffectVertexShader = true;
		bool _isNowAffectPixelShader = true;
		bool _isNowAffectMaterial = true;

	};
}


