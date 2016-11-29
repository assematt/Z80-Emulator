#pragma once

#include "TResourceVector.h"
#include "IDGenerator.h"

namespace nne
{
	struct TCacheManager
	{
		using TResourceTypeID = std::size_t;
		
		static TCacheManager& getInstance()
		{
			static TCacheManager Instance;
			return Instance;
		}

		template <class _Type>
		void addResource(typename TResourceLoader<_Type>& Resource)
		{
			//TResourceTypeID ID = TUtility::getTypeID<TResourceTypeID, _Type>();
			TResourceTypeID ID = idgenerator::GenerateByType::getUniqueID<TResourceTypeID, _Type>();

			if (mResourcesVectors.find(ID) == mResourcesVectors.end())
			{
				mResourcesVectors.emplace(ID, IResourceVectorBase());
			}

			(static_cast<TResourceVector<_Type>*>(&mResourcesVectors[ID]))->addResource(Resource);
		}

		template <class _Type>
		typename _Type& getResource(const std::string& Key)
		{
			//TResourceTypeID ID = TUtility::getTypeID<TResourceTypeID, _Type>();
			TResourceTypeID ID = idgenerator::GenerateByType::getUniqueID<TResourceTypeID, _Type>();

			return ((static_cast<TResourceVector<_Type>*>(&mResourcesVectors[ID]))->getResource(Key));
		}
	private:
		std::map<TResourceTypeID, IResourceVectorBase> mResourcesVectors;
	};
}