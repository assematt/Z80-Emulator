#pragma once

#include <vector>
#include <string>
#include <atomic>

namespace nne
{

	struct ILoadingScreen
	{
		/// Function to setup the files to load
		virtual void setup() = 0;

		/// Function that execute the loading
		virtual void loading(std::atomic_bool& IsDone) = 0;

	protected:
		std::vector<std::string> mFiles;
	};

	
}