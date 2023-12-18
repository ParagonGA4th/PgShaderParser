#pragma once
#include <shobjidl.h>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <string>
#include <memory>

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
		void OpenFileButtonPressed();
		void SaveFileButtonPressed();
		void NewFileButtonPressed();

		std::string GetCurrentShaderPath() { return _currentShaderPath; }
		std::string GetCurrentMaterialPath() { return _currentMaterialPath; }

		bool IsNowAffectShaderPath() { return _isNowAffectShader; }
		bool IsNowAffectMaterialPath() { return _isNowAffectMaterial; }

	private:
		void ShowOpenFileDialog();
		void ShowSaveFileDialog();
		void ShowNewFileDialog();

	private:
		std::unique_ptr<ShaderParser> _shaderParser;

	private:
		std::string _currentShaderPath;
		std::string _currentMaterialPath;

		bool _isNowAffectShader = true;
		bool _isNowAffectMaterial = true;

	};
}


