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

		TResource<T> loadResource() const
		{
			return mResourceLoader();
		}

		std::string	getResourceID() const
		{
			return mResourceID;
		}

	private:
		std::string mResourceID;
		_TLoadFunction mResourceLoader;
	};
}