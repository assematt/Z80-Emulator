#pragma once

#include <functional>
#include <string>

#include "TResource.h"

namespace nne
{
	template <class T>
	class TResourceLoader
	{

	public:
		using _TLoadFunction = std::function<TResource<T>()>;

	public:
		TResourceLoader(_TLoadFunction ResourceLoader, std::string ResourceID)
			: mResourceLoader(std::move(ResourceLoader))
			, mResourceID(std::move(ResourceID))
		{
		}

		TResource<T> LoadResource() const
		{
			return mResourceLoader();
		}

		std::string	GetResourceID() const
		{
			return mResourceID;
		}

	private:
		std::string mResourceID;
		_TLoadFunction mResourceLoader;
	};
}