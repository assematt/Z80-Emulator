#pragma once


#include <vector>
#include <map>

#include "TResource.h"

namespace nne
{
	class TCacheManager
	{
	public:

		/// Constructor
		TCacheManager();

		/// Data loading
		bool LoadFromFile(const std::string& Path);
		bool LoadFromMemory(const void* Data, std::size_t DataSize);
		bool LoadFromStream(sf::InputStream& Stream);

	private:
		std::vector<TResource<void*>> mResourceVector;
	};
}