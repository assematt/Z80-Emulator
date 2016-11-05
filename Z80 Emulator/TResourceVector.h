#pragma once

#include <map>

#include "TResourceLoader.h"

namespace nne
{
	struct IResourceVectorBase
	{
		std::map<std::string, TResourceGeneric> mResources;
	};

	template <class _Type>
	class TResourceVector : public IResourceVectorBase
	{
	public:

		virtual ~TResourceVector() {}

		void AddResource(typename TResourceLoader<_Type>& Resource)
		{
			auto TempPtr = Resource.LoadResource();
			auto TempID = Resource.GetResourceID();
			auto RealPtr = std::make_unique<void*>(TempPtr.release());

			mResources.insert(std::pair<std::string, TResourceGeneric>(TempID, std::move(RealPtr)));
		}

		_Type& GetResource(const std::string& Key)
		{
			auto TempPtr = *mResources[Key];
			auto ReturnPtr = static_cast<_Type*>(TempPtr);

			return *ReturnPtr;
		}
	};
}