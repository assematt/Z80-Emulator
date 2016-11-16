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

		void addResource(typename TResourceLoader<_Type>& Resource)
		{
			auto TempPtr = Resource.loadResource();
			auto TempID = Resource.getResourceID();
			auto RealPtr = std::make_unique<void*>(TempPtr.release());

			mResources.insert(std::pair<std::string, TResourceGeneric>(TempID, std::move(RealPtr)));
		}

		_Type& getResource(const std::string& Key)
		{
			auto TempPtr = *mResources[Key];
			auto ReturnPtr = static_cast<_Type*>(TempPtr);

			return *ReturnPtr;
		}
	};
}