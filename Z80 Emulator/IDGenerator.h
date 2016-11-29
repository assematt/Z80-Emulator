#pragma once

#include <map>

namespace nne
{
	namespace idgenerator
	{
		using GlobalID = std::size_t;

		struct GenerateByType
		{

			template <class IDType, class Type>
			static inline IDType getUniqueID() noexcept
			{
				//std::string ClassName = typeid(Type).name();
				static IDType typeID = generateID<IDType>();
				return typeID;
			}

		private:
			template <class IDType>
			static inline IDType generateID() noexcept
			{
				static IDType lastID = 0u;
				return lastID++;
			}
		};

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