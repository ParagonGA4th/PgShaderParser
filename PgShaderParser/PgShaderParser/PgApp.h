#pragma once
#include <fstream>
#include <filesystem>
#include <cassert>
#include <string>
#include <memory>

#include "PgDefineEnums.h"

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
		ShaderParser* GetShaderParser();

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

		std::wstring GetVSName();
		std::wstring GetPSName();
		std::wstring GetMaterialName();

	private:
		std::unique_ptr<ShaderParser> _shaderParser;
	};
}


