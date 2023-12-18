#pragma once
#include <shobjidl.h>
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
		void OpenFileButtonPressed(eShaderType shaderType);
		void SaveFileButtonPressed();
		void NewFileButtonPressed();

		std::wstring GetCurrentVertexShaderPath() { return _currentVSPath; }
		std::wstring GetCurrentPixelShaderPath() { return _currentPSPath; }
		std::wstring GetCurrentMaterialPath() { return _currentMaterialPath; }

		bool IsNowAffectShaderPath() { return _isNowAffectShader; }
		bool IsNowAffectMaterialPath() { return _isNowAffectMaterial; }

	private:
		void ShowOpenFileDialog(eShaderType shaderType);
		void ShowSaveFileDialog();
		void ShowNewFileDialog();

	private:
		std::unique_ptr<ShaderParser> _shaderParser;

	private:
		std::wstring _currentVSPath;
		std::wstring _currentPSPath;
		std::wstring _currentMaterialPath;

		bool _isNowAffectShader = true;
		bool _isNowAffectMaterial = true;

	};
}


