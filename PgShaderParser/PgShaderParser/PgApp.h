#pragma once
#include <shobjidl.h>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <string>

namespace Pg
{
	class PgApp
	{
	public:
		PgApp();
		~PgApp();

		void Initialize();
		void Loop();
		void Finalize();

		void OpenFileButtonPressed();
		void SaveFileButtonPressed();
		void EditFileButtonPressed();
	private:
		void ShowOpenFileDialog();
		void ShowSaveFileDialog();
		void ShowEditFileDialog();

	private:
		std::string _currentShaderPath;
		std::string _currentMaterialPath;

	};
}


