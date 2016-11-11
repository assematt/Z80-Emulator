#pragma once

#include <vector>
#include <string>
#include <atomic>

namespace nne
{

	struct ILoadingScreen
	{
		/// Function to setup the files to load
		virtual void Setup() = 0;

		/// Function that execute the loading
		virtual void Loading(std::atomic_bool& IsDone) = 0;

	protected:
		std::vector<std::string> mFiles;
	};

	
}