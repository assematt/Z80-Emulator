#pragma once

#include <SFML/System/FileInputStream.hpp>
#include <memory>

namespace nne
{

	template <class T>
	class TResource
	{
	public:
		using TResourceType = T;
		using TResourceID = std::size_t;
		using TResourcePtr = std::shared_ptr<T>;

		/// Constructor
		TResource();
		virtual ~TResource() {}

		/// Data loading
		bool LoadFromFile(const std::string& Path);
		bool LoadFromMemory(const void* Data, std::size_t DataSize);
		bool LoadFromStream(sf::InputStream& Stream);

		/// Function to check if this resource is cached or not
		bool IsDataCached();

		/// Get data
		std::shared_ptr<T>& GetResourceData();
		const std::shared_ptr<T>& GetResourceData() const;
		const TResourceID GetResourceID() const;

		/// Operators
		T& TResource<T>::operator*();

		/// Function to release the data in memory
		void FreeData();

	private:
		TResourcePtr mData;
		TResourceID mDataID;
	};

	template <typename T>
	inline TResource<T>::TResource()
	{
		mData = std::make_shared<T>();
	}

	template <typename T>
	inline bool TResource<T>::LoadFromFile(const std::string& Path)
	{
		return mData->loadFromFile(Path);
	}

	template <typename T>
	inline bool TResource<T>::LoadFromMemory(const void* Data, std::size_t DataSize)
	{
		return mData->loadFromMemory(Data, DataSize);
	}

	template <typename T>
	inline bool TResource<T>::LoadFromStream(sf::InputStream& Stream)
	{
		return mData->loadFromStream(Stream);
	}

	template <typename T>
	inline bool TResource<T>::IsDataCached()
	{
		return false;
	}

	template<typename T>
	inline typename std::shared_ptr<T>& TResource<T>::GetResourceData()
	{
		return mData;
	}

	template <class T>
	inline const typename std::shared_ptr<T>& TResource<T>::GetResourceData() const
	{
		return mData;
	}

	template <typename T>
	inline const typename TResource<T>::TResourceID TResource<T>::GetResourceID() const
	{
		return mDataID;
	}

	template<class T>
	inline T& TResource<T>::operator*()
	{
		return *mData;
	}

	template <typename T>
	inline void TResource<T>::FreeData()
	{

	}
}