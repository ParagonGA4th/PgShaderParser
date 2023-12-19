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
	};
}


