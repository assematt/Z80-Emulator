#pragma once

#include "TResourceVector.h"

namespace nne
{
	struct TCacheManager
	{
		using TResourceTypeID = std::size_t;
		
		static TCacheManager& GetInstance()
		{
			static TCacheManager Instance;
			return Instance;
		}

		template <class _Type>
		void AddResource(typename TResourceLoader<_Type>& Resource)
		{
			TResourceTypeID ID = TUtility::GetTypeID<TResourceTypeID, _Type>();

			if (mResourcesVectors.find(ID) == mResourcesVectors.end())
			{
				mResourcesVectors.emplace(ID, IResourceVectorBase());
			}

			(static_cast<TResourceVector<_Type>*>(&mResourcesVectors[ID]))->AddResource(Resource);
		}

		template <class _Type>
		typename _Type& GetResource(const std::string& Key)
		{
			TResourceTypeID ID = TUtility::GetTypeID<TResourceTypeID, _Type>();

			return ((static_cast<TResourceVector<_Type>*>(&mResourcesVectors[ID]))->GetResource(Key));
		}
	private:
		std::map<TResourceTypeID, IResourceVectorBase> mResourcesVectors;
	};
}