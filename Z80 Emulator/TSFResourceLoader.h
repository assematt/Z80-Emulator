#pragma once

#include <SFML/System/InputStream.hpp>
#include <string>
#include <memory>

#include "TResource.h"

namespace nne
{
	/// Load a resource from file
	template <class _Type>
	struct SFPathLoader
	{
		SFPathLoader(const std::string& Path) :
			mPath(Path)
		{
		}

		TResource<_Type> operator() ()
		{
			std::unique_ptr<_Type> TempPtr = std::make_unique<_Type>();
			TempPtr->loadFromFile(mPath);
			return TempPtr;
		}

	private:
		std::string mPath;
	};

	/// Load a resource from memory
	template <class _Type>
	struct SFMemoryLoader
	{
		SFMemoryLoader(const void* Data, std::size_t Size) :
			mData(Data),
			mSize(Size)
		{
		}

		TResource<_Type> operator() ()
		{
			std::unique_ptr<_Type> TempPtr = std::make_unique<_Type>();
			TempPtr->loadFromMemory(mData, mSize);
			return TempPtr;
		}

	private:
		void* mData;
		std::size_t mSize;
	};

	/// Load a resource from memory
	template <class _Type>
	struct SFStreamLoader
	{
		SFStreamLoader(sf::InputStream& Stream) :
			mStream(&Stream)
		{
		}

		TResource<_Type> operator() ()
		{
			std::unique_ptr<_Type> TempPtr = std::make_unique<_Type>();
			TempPtr->loadFromMemory(mStream);
			return TempPtr;
		}

	private:
		sf::InputStream* mStream;
	};
}