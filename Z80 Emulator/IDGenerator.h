#pragma once

#include <map>

namespace nne
{
	namespace idgenerator
	{
		using GlobalID = std::size_t;

		struct GenerateByString
		{
			static GlobalID getUniqueID(const std::string& IDKey)
			{
				static std::map<std::string, GlobalID> mIDMap;
				static GlobalID mLastID;

				return mIDMap.count(IDKey) == 1 ? mIDMap[IDKey] : mIDMap[IDKey] = mLastID++;
			}
		};
	}
}