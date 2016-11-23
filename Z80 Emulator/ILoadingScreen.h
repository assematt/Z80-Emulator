#pragma once

#include <vector>
#include <string>
#include <atomic>
#include <memory>

#include "IScene.h"

namespace nne
{
	namespace tgui
	{
		struct ILoadingScreen
		{
			using Ptr = std::unique_ptr<ILoadingScreen>;

			/// Function that execute the loading
			virtual void loading(std::atomic_bool& IsDone) = 0;

		protected:
			std::vector<std::string> mFiles;
		};
	}	
}